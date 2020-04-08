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
    
    // open inFile
    pInFile = fopen(argv[1], "rb");
    if(pInFile == NULL){
        fprintf(stderr, "%s doesn't exist or is inaccessible\n", argv[1]);
        exit(1);
    }

    // open outFile
    pOutFile = fopen(argv[2], "wb+"); // new file created if not exist 
    
    // Get inFile's size in bytes, initialize address arrays
    stat(argv[1], &inFileInfo);
    iFileSize = ((int) inFileInfo.st_size / 8);
    unsigned long lLogicalAddressM[iFileSize];
    unsigned long lPhysicalAddressM[iFileSize];

    // for each row in the file, calculate physical memory
    for(i = 0; i < iFileSize; i++){
        // populate logical address array
        fseek(pInFile, (i * 8), SEEK_SET); // every 8 bytes
        fread(&lLogicalAddressM[i], 8, 1L, pInFile);

        // generate physical address
        iFrameNum = (int) lLogicalAddressM[i] / PAGE_SIZE;
        iFrameOffset = (int) lLogicalAddressM[i] % PAGE_SIZE;
        lPhysicalAddressM[i] = (unsigned long) 
            (iPageTableM[iFrameNum] * PAGE_SIZE) + iFrameOffset;

        // write to file
        fseek(pOutFile, (i * 8), SEEK_SET);
        fwrite(&lPhysicalAddressM[i], 8, 1L, pOutFile);
    }

    fclose(pInFile);
    fclose(pOutFile);

    return 0;
}
