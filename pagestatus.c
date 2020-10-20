#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

#define PGSIZE sysconf(_SC_PAGE_SIZE)

typedef struct {
    char* filename;
    int fsync;
} Args;

typedef struct {
	uint64_t vpn;
    uint64_t pfn;
    int is_file_page;
    int is_dirty;
} PagedetailsEntry;

int pagemap_fd;
int kpage_fd;

void init() 
{
	char pagemap_file[BUFSIZ];
	snprintf(pagemap_file, sizeof(pagemap_file), "/proc/%ju/pagemap", (uintmax_t)getpid());
    assert((pagemap_fd = open(pagemap_file, O_RDONLY)) > 0);
	assert((kpage_fd = open("/proc/kpageflags", O_RDONLY)) > 0);
}

void teardown() 
{
	close(pagemap_fd);
	close(kpage_fd);
}

int get_dirty_bit(uint64_t pfn)
{
    uint64_t data;
    assert(pread(kpage_fd, ((uint8_t*)&data), sizeof(data), pfn * sizeof(data)) == sizeof(data));
    // return the dirty bit
    return ((data >> 4) & 0x1); 
}

PagedetailsEntry* get_page_details(uintptr_t vaddr)
{
    uint64_t data;
    uintptr_t vpn;
    PagedetailsEntry* entry = (PagedetailsEntry*) malloc(sizeof(PagedetailsEntry));
      
    vpn = vaddr / PGSIZE;
    entry->vpn = vpn;
    assert(pread(pagemap_fd, ((uint8_t*)&data), sizeof(data), vpn * sizeof(data)) == sizeof(data));

    // 55 bits is pfn
    // if pfn is 0, we have a problem somewhere
    entry->pfn = data & (((uint64_t)1 << 55) - 1);
    assert(entry->pfn); 

    // 61 is file_page
    entry->is_file_page = (data >> 61) & 1;

    entry->is_dirty = entry->is_file_page? get_dirty_bit(entry->pfn): -1;
    return entry;
}

void* overwrite_file(void* ptr) {
    // this function just overwrites all blocks
    // of an existing file.
    // it doesn't append new blocks (maybe good to handle new pages?). 
	Args* args = (Args*) ptr;
	
	int fd;
	assert((fd = open (args->filename, O_RDWR)) > 0);

	struct stat sb;
	assert(stat(args->filename, &sb) != -1); 
	int pages = sb.st_size/PGSIZE;
    if(pages <= 0) {
        printf("Make sure %s has at least one block\n", args->filename);
        exit(-1);
    }

	char* buf = (char*) malloc(sizeof(char) * PGSIZE);
	memset(buf, 65, PGSIZE);
	
	// write every other page
	for(int i = 0; i < pages; i = i + 2) 
		assert(pwrite(fd, buf, PGSIZE, i * PGSIZE) == PGSIZE);

	if(args->fsync)
		assert(!fsync(fd));
}

int main(int argc, char **argv)
{
    uintptr_t vaddr;
    int fd, i;
    long NUMPAGES;
    char* dummy;
    struct timeval start, end;

    if(geteuid()) {
  		printf("Aborting. Run as sudo.\n");
  		exit(-1);
	}

    if(argc != 4) {
        printf("Usage: %s filename num_pages fsync_or_not\nexample: %s foo 5 1\n", argv[0], argv[0]);
        exit(-1);
    }

    NUMPAGES = strtol(argv[2], &dummy, 10);
    if (NUMPAGES <= 0)
    	printf("Warning: NUMPAGES must be an integer > 0.\n");

    if((fd = open(argv[1], O_RDWR)) <= 0) {
        printf("Error opening file %s. Make sure it exists.\n", argv[1]);
        exit(-1);
    }

    // MAP_POPULATE is necessary; otherwise, Linux delays creating the PT entries and thus pfns will be 0...
    vaddr = (uintptr_t) mmap(NULL, NUMPAGES * PGSIZE, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0);

    // overwrite some portions of the file, optionally fsync the file
    Args args;
    args.filename = argv[1]; 
    args.fsync = strtol(argv[3], &dummy, 10);
    overwrite_file(&args);

	init();
	gettimeofday(&start,NULL);
	for(i = 0; i < NUMPAGES; i++) {
	    PagedetailsEntry* entry = get_page_details(vaddr + i * PGSIZE);
	    printf("vpn:%lu, pfn:%lu, is_file_page:%d, is_dirty:%d\n", entry->vpn, entry->pfn, entry->is_file_page, entry->is_dirty);
	}
	gettimeofday(&end,NULL);
	int elapsed = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
	teardown();
	// printf("Took total %d us to query %ld pages, avg query time = %f us\n", elapsed, NUMPAGES, elapsed * 1.0/NUMPAGES);
    return 0;
}