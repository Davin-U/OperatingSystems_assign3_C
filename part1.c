#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    int i, iFileSize;
    unsigned long lAddress, lAddressM[8]; // logical memory address
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
    iFileSize = ((int) inFileInfo.st_size / 8);

    // populate logical memory address array
    for(i = 0; i < iFileSize; i++){ // read every 8 bytes
        fseek(pInFile, (i * 8), SEEK_SET);
        fread(&lAddress, 8, 1L, pInFile); // reads 8 bytes into lBuffer
        lAddressM[i] = lAddress;      
    }
    
    return 0;
}

