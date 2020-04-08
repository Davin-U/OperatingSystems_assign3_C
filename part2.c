#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "assign3p2.h"

int main(int argc, char** argv) {
    FILE *pInFile, *pOutFile;
    int i, j, k, iFileSize, iClock = 0, bFindLRU;
    int iPageNum, iOffset, iPageFault = 0;
    ptEntry pageTableM[MAX_STACK_ELEM], tempEntry;
    struct stat inFileInfo;
    Stack stackLRU = newStack();  // bottom value is LRU process
    Stack stackTemp = newStack(); // we pop values onto it, pop back to LRU     
    Element element, popped;
    
    // Check if command line args are valid
    if(argc != 3){
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

    // Initialize pageTable array
    tempEntry.bValid = FALSE;
    tempEntry.iPageNum = 999999;
    for(i = 0; i < MAX_STACK_ELEM; i++){
        pageTableM[i] = tempEntry;
    }

    // for each row in the file, calculate virtual memory
    for(i = 0; i < iFileSize; i++){
        iClock++;
        bFindLRU = TRUE;

        // populate logical address at index
        fseek(pInFile, (i * 8), SEEK_SET); // every 8 bytes
        fread(&lLogicalAddressM[i], 8, 1L, pInFile);

        // generate page number
        iPageNum = (int) lLogicalAddressM[i] / PAGE_SIZE;
        iOffset = (int) lLogicalAddressM[i] % PAGE_SIZE;
        
        // attempt to push page onto pageTable
        for(j = 0; j < MAX_STACK_ELEM; j++){
            tempEntry = pageTableM[j];
            
            // Entry is available
            if(tempEntry.bValid == FALSE){ // Entry available
                tempEntry.bValid = TRUE;
                tempEntry.iPageNum = iPageNum;
                pageTableM[i] = tempEntry;
                iPageFault++;
                element.iPageNum = iPageNum;
                push(stackLRU, element);
                bFindLRU = FALSE;
                break;
            }

            // Entry is a match
            if(tempEntry.iPageNum == iPageNum){
                // pop till we find number in LRU stack
                while(isEmpty(stackLRU) == FALSE){
                    popped = pop(stackLRU);
                    if(popped.iPageNum == iPageNum){
                        while(isEmpty(stackTemp) == FALSE)
                            push(stackLRU, pop(stackTemp));
                        push(stackLRU, popped); // Puts match on top of LRU stack
                        break;
                    }
                    push(stackTemp, popped);
                }
                bFindLRU = FALSE;
                break;
            }
        }

        // No available entries, no matches in pageTable
        if(bFindLRU){
            while(isEmpty(stackLRU) == FALSE){
                popped = pop(stackLRU);
                if(isEmpty(stackLRU)){ // We've reached our LRU
                    // update pageTableM with iPageNum, put iPageNum ontop of stack
                    for(k = 0; k < MAX_STACK_ELEM; k++){
                        tempEntry = pageTableM[k];
                        if(popped.iPageNum == tempEntry.iPageNum){
                            tempEntry.bValid = TRUE;
                            tempEntry.iPageNum = iPageNum;
                            pageTableM[k] = tempEntry;
                            iPageFault++;
                            while(isEmpty(stackTemp) == FALSE)
                                push(stackLRU, pop(stackTemp));
                            element.iPageNum = iPageNum;
                            push(stackLRU, element);
                            break;
                        }

                    }
                    break;
                }
                push(stackTemp, popped);
            }
        }

        // Print out info for each Virtual address
        //printf("Clock: %d, PageNum: %d, offset: %d\n"
        //    , iClock, iPageNum, iOffset);

        // write to file
        fseek(pOutFile, (i * 8), SEEK_SET);
        fwrite(&lLogicalAddressM[i], 8, 1L, pOutFile);
    }
    
    printf("%d\n", iPageFault);

    fclose(pInFile);
    fclose(pOutFile);
    freeStack(stackLRU);
    freeStack(stackTemp);

    return 0;
}
