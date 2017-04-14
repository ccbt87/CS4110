#ifndef HEADER_STACK
#define HEADER_STACK

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void push(int id);
int pop();
int peek();
void printStack(char* name);
void create();

struct block
{
    int scope;
    struct block* next;

};

struct stack
{
    struct block* head;
    void (*push)(int);
    int (*pop)();
    void (*printStack)(char*);
    void (*create)();
    int (*peek)();

};

struct stack* _stack;

void create()
{
    _stack = calloc(1, sizeof(struct stack));
    _stack->head = NULL;
}

void push(int id)
{
    struct block *newBlock;
    if(!_stack->head)
    {
        newBlock = malloc(1*sizeof(struct block));
        newBlock->scope = id;
        newBlock->next = NULL;
        _stack->head = newBlock;
        return;
    }
    newBlock = malloc(1*sizeof(struct block));
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