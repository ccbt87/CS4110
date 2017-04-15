#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int pop_scope;
typedef struct
{
    int scope;
    struct block* next;

}block;

typedef struct
{
    block* head;
    block*(*push)(block* b, int id);
    block*(*pop)(block* b);
    void (*printStack)(block* h, char*);
    int (*peek)(block* h);

}Stack;

block* push(block* b, int id)
{
    block *newBlock;
    if(!b)
    {
        newBlock = malloc(sizeof(newBlock));
        newBlock->scope = id;
        newBlock->next = NULL;
        b = newBlock;
        return b;
    }
    newBlock = malloc(sizeof(newBlock));
    newBlock->next = b;
    newBlock->scope = id;
    b = newBlock;
    return b;

}

block* pop(block* b)
{
    int scope = b->scope;
    block* myTemp;
    myTemp = b;
    b = myTemp->next;
    pop_scope = scope;
    return b;
}

int peek(block* h)
{
    return h->scope;
}

void printStack(block* h, char* name)
{
    block* myBlock;
    if(h)
    {
        printf("%s Contents\n", name);
        myBlock = h;
        while(myBlock != NULL)
        {
            printf("Block ID: %i\n", myBlock->scope);
            myBlock = myBlock->next;
        }
    }
    free(myBlock);
}

#endif
