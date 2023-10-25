#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Seek to the beginning of the file
    fseek(file, 0, SEEK_SET);

    int bufferSize = 100;
    int skipSize = 4096;
    char buffer[bufferSize];
    size_t bytesRead;
    char *start, *end;
    char oid[25] = "";
    char prevOid[25] = "";
    char offset[25] = "";
    while (!feof(file)) {
        // Read 100 bytes
        bytesRead = fread(buffer, 1, bufferSize, file);

        if (bytesRead == 0) {
            break;
        }

	start = strstr(buffer, "<<<");
        end = strstr(buffer, ">");
	int j;
        if (start && end && start < end) {
            // Print the portion between '<<<' and '>>>'
            // fwrite(start + 3, 1, end - start - 3, stdout);
	    for (j=0; j<end-start-3; j++) {
		oid[j] = *(start+3+j);
	    }
	    oid[j] = '\0';
        }
	
	start = strstr(buffer, ",<");
        end = strstr(buffer, ">>>");

        if (start && end && start < end) {
            // Print the portion between '<<<' and '>>>'
            //fwrite(start + 1, 1, end - start - 3, stdout);
	    for (j=0; j<end-start-2; j++) {
                offset[j] = *(start+2+j);
            }
            offset[j] = '\0';
        }
	
	//printf("0x%llx,%s\n", atoll(oid), offset);
	if (strcmp(prevOid, oid)){
	    strcpy(prevOid, oid);
	    printf("%s\t%s\n", oid, offset); // offset should be 0 or 4190208 
	}
	
	// Seek to the next 4096th byte
        fseek(file, skipSize - bufferSize, SEEK_CUR);
    }

    fclose(file);
    return 0;
}
