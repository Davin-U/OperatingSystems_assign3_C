#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define PAGE_SIZE 128

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    int i, iFileSize, iPageTableM[] = {2, 4, 1, 7, 3, 5, 6};
    int iFrameNum, iFrameOffset;
    struct stat inFileInfo;
    
    if(argc != 3){ // comand line arguments
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        exit(1);
    }

    pInFile = fopen(argv[1], "r"); // open file
    if(pInFile == NULL){
        fprintf(stderr, "%s doesn't exist or is inaccessible\n", argv[1]);
        exit(1);
    }
    
    // Get inFile's size in bytes, initialize logical address array
    stat(argv[1], &inFileInfo);
    iFileSize = ((int) inFileInfo.st_size / 8);
    unsigned long lAddressM[iFileSize]; // Logical Memory addresses

    // populate logical address array
    for(i = 0; i < iFileSize; i++){
        // populate logical address array
        fseek(pInFile, (i * 8), SEEK_SET); // every 8 bytes
        fread(&lAddressM[i], 8, 1L, pInFile);

        // generate physical address
        iFrameNum = (int) lAddressM[i] / PAGE_SIZE;
        iFrameOffset = (int) lAddressM[i] % PAGE_SIZE;
        printf("%d, %d\n", iFrameNum, iFrameOffset);
    }

    return 0;
}
