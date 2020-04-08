#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "assign3p2.h"

void push(Stack stack, Element value)
{
    if (stack->iCount >= MAX_STACK_ELEM)
        errExit("Attempt to PUSH more than %d values on the array stack"
        , MAX_STACK_ELEM);
    else
    {
        stack->stackElementM[stack->iCount] = value;
        stack->iCount++;
    }
}

Element pop(Stack stack)
{
    if (isEmpty(stack))
        errExit("Attempt to POP an empty array stack");
    else
    {
        stack->iCount--;
        return stack->stackElementM[stack->iCount];
    }
}

Element topElement(Stack stack)
{
    if (isEmpty(stack))
        errExit("Attempt to examine topElement of an empty array stack");
    else
        return stack->stackElementM[stack->iCount-1];    // return the top
}

int isEmpty(Stack stack)
{
    return stack->iCount <= 0;
}

Stack newStack()
{
    Stack stack = (Stack) malloc(sizeof(StackImp));
    stack->iCount = 0;
    return stack;
}

void freeStack(Stack stack)
{
    free (stack);
}

void errExit(char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n\tEncountered in file %s\n", __FILE__);  // this 2nd arg is filled in by
                                // the pre-compiler
    exit(ERR_EXIT);
}
