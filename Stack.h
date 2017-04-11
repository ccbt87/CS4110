#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void push(int);
int pop();
int peek();
int* list();
void printStack(char* name);

struct block
{
    int scope;
    struct block* next;
    void (*push)(int id);
    int (*pop)();
    int  (*peek)();
    int* (*list)();
    void (*printStack)(char*);
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

int pop()
{
    int scope = head->scope;
    struct block* myTemp;
    myTemp = head->next;
    free(head);
    head = myTemp;
    return scope;
}

int peek()
{   
    return head->scope;
}

int* list()
{
    int length = 0;
    struct block* myBlock;
    if(head)
    {
        myBlock = head;
        while(myBlock != NULL)
        {
            myBlock = myBlock->next;
            length++;
        }
        int* scopes = (int*)malloc(length * sizeof(int));
        myBlock = head;
        int i;
        for (i = 0; i < length; i++)
        {
            scopes[i] = myBlock->scope;
            myBlock = myBlock->next;
        }
        return scopes;
    }
    return NULL;
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
