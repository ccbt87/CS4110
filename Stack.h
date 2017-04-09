#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void push(int);
void pop();
void printStack(char* name);

struct block
{
    int scope;
    struct block* next;
    void (*push)(int id);
    void (*pop)();
    void (*printStack)(char*)

}*head;

void push(int id)
{
    struct block *newBlock;
    if(!head)
    {
        head = (struct block *)malloc(1*sizeof(struct block));
        head->scope = id;
        head->next = NULL;
        return;
    }
    newBlock = (struct block *)malloc(1*sizeof(struct block));
    newBlock->next = head;
    newBlock->scope = id;
    head = newBlock;
}

void pop()
{
    struct block* myTemp;
    myTemp = head->next;
    free(head);
    head = myTemp;
}

void printStack(char* name)
{
    struct block* myBlock;
    if(head)
    {
        printf("%s Contents\n", name);
        myBlock = head;
        while(myBlock != NULL)
        {
            printf("Block ID: %i\n", myBlock->scope);
            myBlock = myBlock->next;
        }
    }
}

#endif
