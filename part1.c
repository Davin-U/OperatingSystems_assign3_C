#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    
    // Check if files exist
    if(argc != 2){
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        exit(1);
    }
    
    return 0;
}
