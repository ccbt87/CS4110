#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void create();
void push(int id);
int pop();
int peek();
int* list();
void printStack(char* name);

struct block
{
    int scope;
    struct block* next;

};

struct stack
{
    int size;
    struct block* head;
    void (*create)();
    void (*push)(int);
    int (*pop)();
    int  (*peek)();
    int* (*list)();
    void (*printStack)(char*);
};

struct stack* _stack;

void create()
{
    _stack = (struct stack *)calloc(1, sizeof (struct stack));
    _stack->head = NULL;
}

void push(int id)
{
    struct block *newBlock;
    if(!_stack->head)
    {
        newBlock = (struct block *)malloc(1*sizeof(struct block));
        newBlock->scope = id;
        newBlock->next = NULL;
        _stack->head = newBlock;
        return;
    }
    newBlock = (struct block *)malloc(1*sizeof(struct block));
    newBlock->next = _stack->head;
    newBlock->scope = id;
    _stack->head = newBlock;
}

int pop()
{
    int scope = _stack->head->scope;
    struct block* myTemp;
    myTemp = _stack->head->next;
    free(_stack->head);
    _stack->head = myTemp;
    return scope;
}

int peek()
{   
    return _stack->head->scope;
}

int* list()
{
    struct block* myBlock;
    int size = _stack->size;
    if(size > 0)
    {
        int* scopeList = (int*)malloc(size * sizeof(int));
        myBlock = _stack->head;
        int i;
        for (i = 0; i < size; i++)
        {           
            scopeList[i] = myBlock->scope;
            myBlock = myBlock->next;            
        }
        return scopeList;
    }
    return NULL;
}

void printStack(char* name)
{
    struct block* myBlock;
    if(_stack->head)
    {
        printf("%s Contents\n", name);
        myBlock = _stack->head;
        while(myBlock != NULL)
        {
            printf("Block ID: %i\n", myBlock->scope);
            myBlock = myBlock->next;
        }
    }
}

#endif
