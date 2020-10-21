# filepagestatus
A simple tool to know status of file pages in Linux. See run.sh for usage.

Notes:
Blocks written to a file are buffered in the Linux buffercache. Either an fsync from the application or a periodic transaction commit (on ext4)/pdflush write is required to sync the contents to the underlying device. If a page is written down (in-mem copy == on-disk copy), the dirty bit is 0, otherwise 1. This tool reads this dirty bit info for a given file.

How it works:
First, the file is mapped using mmap. We use the MAP_POPULATE flag to indicate that the pages must be prefaulted (i.e., the mappings must NOT be lazily created which is the default in Linux). We use the file's size (as reported by stat) as the mapping length. Note that the file size can change after the mapping is created (because of some blocks being appended to the file). The tool then uses the pagemap proc fs (more details here: https://www.kernel.org/doc/Documentation/vm/pagemap.txt) to get the pfn of the mapped page. Then, it uses the kpageflags file to read the flags of a page. Specifically, it finds if pages are dirty or not. 

Important: if the file grows in size after the mmap call, then, the pfn cannot be retrieved correctly (even with MAP_POPULATE). Two ways to solve this: one, the grown region must be accessed in someway so that the mapping is created. Second, the mmap call can be issued after we know that all writes have been made to the file but not synced yet.  
