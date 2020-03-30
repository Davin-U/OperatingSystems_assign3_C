#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    int i, iFileSize;
    unsigned long lBuffer;
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
    
    // Get inFile's size in bytes
    stat(argv[1], &inFileInfo);
    iFileSize = (int) inFileInfo.st_size;

    for(i = 0; i < iFileSize; i += 8){ // read every 8 bytes
        fseek(pInFile, i, SEEK_SET);
        fread(&lBuffer, 8, 1L, pInFile); // reads 8 bytes into lBuffer
        printf("%d ", i);
        printf("%lx\n", lBuffer);       
    }
    
    return 0;
}

