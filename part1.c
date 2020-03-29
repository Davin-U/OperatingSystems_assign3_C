#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    int i, j;
    unsigned long lBuffer;
    
    printf("%d\n", argc);

    // Check if files exist
    if(argc != 3){
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        exit(1);
    }

    pInFile = fopen(argv[1], "r");
    if(pInFile == NULL){
        fprintf(stderr, "%s either doesn't exist or is inaccessible\n", argv[1]);
        exit(1);
    }
    
    for(i = 0; i < 64; i += 8){
        fseek(pInFile, i, SEEK_SET);
        fread(&lBuffer, 8, 1L, pInFile); // reads 8 bytes into lBuffer
        printf("%lu\n", lBuffer);       
    }
    
    return 0;
}

