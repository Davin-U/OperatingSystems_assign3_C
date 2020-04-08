// Maximum constants
#define PAGE_SIZE 128           // Used to calculate pages and frames
#define MAX_STACK_ELEM 7        // Maximum number of elements in the stack array
#define MAX_TOKEN 50            // Maximum number of actual characters for a token
#define ERR_EXIT 999            // Unexpected error
#define FALSE 0
#define TRUE 1

typedef struct
{
    int iPageNum;
} Element;

typedef struct
{
    int bValid;
    int iPageNum; 
} ptEntry;

// StackImp typedef defines how we implement a stack using an array
typedef struct
{
    int iCount;  // number of elements in stack
    Element stackElementM[MAX_STACK_ELEM];
} StackImp;

// Stack typedef defines a pointer to a stack
typedef StackImp *Stack;

// Stack functions
void push(Stack stack, Element value);
Element pop(Stack stack);
int isEmpty(Stack stack);
Stack newStack();
void freeStack(Stack stack);
Element topElement(Stack stack);

// Utility routines
void errExit(char szFmt[], ...);
