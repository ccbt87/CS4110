#ifndef HEADER_STACK
#define HEADER_STACK

struct block
{
    int scope;
    struct block* next;
};

struct Stack
{
    struct block* head;
    struct block*(*push)(struct block* b, int id);
    struct block*(*pop)(struct block* b);
    void (*printStack)(struct block* b, char*);
    int (*peek)(struct block* b);
};

struct block* push(struct block* b, int id)
{
    struct block* newBlock;
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

struct block* pop(struct block* b)
{
    int scope = b->scope;
    struct block* myTemp;
    myTemp = b;
    b = myTemp->next;
    return b;
}

int peek(struct block* b)
{
    return b->scope;
}

void printStack(struct block* b, char* name)
{
    struct block* myBlock;
    if(b)
    {
        printf("%s Contents\n", name);
        myBlock = b;
        while(myBlock != NULL)
        {
            printf("Block ID: %i\n", myBlock->scope);
            myBlock = myBlock->next;
        }
    }
    else
    {
        printf("%s Contents nothing\n", name);
    }
}

#endif
