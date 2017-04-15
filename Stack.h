#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"


struct block
{
    int scope;
    struct block* next;

};

struct stack
{
    struct block* head;
    struct block*(*push)(struct block* b, int id);
    int (*pop)(struct block* b);
    void (*printStack)(struct block* h, char*);
    int (*peek)(struct block* h);

};

struct block* push(struct block* b, int id)
{
    struct block *newBlock;
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

int pop(struct block* b)
{
    int scope = b->scope;
    struct block* myTemp;
    myTemp = b;
    b = myTemp->next;
    //free(myTemp);
    return scope;
}

int peek(struct block* h)
{
    return h->scope;
}

void printStack(struct block* h, char* name)
{
    struct block* myBlock;
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
