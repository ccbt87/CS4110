#ifndef HEADER_HASH
#define HEADER_HASH

#include "stdlib.h"

struct hash *symbolTable = NULL;
int eleCount = 0;

long long hashkey(char* string, int size);
struct node* findInScope(char* string, int scope, long long index);
void insertToHash(char *string, int scope, int size, long long hashIndex);
void display(int size);
void setSize(int size);

struct node
{
    char* string;
    int scope;
    struct node* next;

};

struct hash
{
    struct node *head;
    int count;
    void (*insertToHash)(char*, int, int, long long);
    void (*display)(int);
    void (*setSize)(int);
    long long (*hashkey)(char*, int);
    struct node* (*findInScope)(char*, int, long long);
};

struct node * createNode(char *s, int scope)
{
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->scope = scope;
    newnode->string = malloc(256);
    strcpy(newnode->string, s);
    newnode->next = NULL;
    return newnode;
};

long long hashkey(char* string, int size)
{
    long long key;

	for (key = 1; *string;)
	{
		key = (key*(long long)(*string++)) % size;
	}
	return (key < 0 ? -key : key);
}

void setSize(int size)
{
   symbolTable = (struct hash *)calloc(size, sizeof (struct hash));
}

struct node* findInScope(char* string, int scope, long long index)
{
    struct node *myNode = NULL;
    if (!symbolTable[index].head)
    {
        return myNode;
    }
    myNode = symbolTable[index].head;
    while(myNode != NULL)
    {
        if((strcmp(myNode->string, string) == 0) && (myNode->scope == scope))
        {
            return myNode;
        }
        myNode = myNode->next;
    }
    return myNode;
}

 void insertToHash(char *string, int scope, int size, long long hashIndex)
{
    struct node *newnode;
    newnode =  createNode(string, scope);

    if (!symbolTable[hashIndex].head)
        {
            symbolTable[hashIndex].head = newnode;
            symbolTable[hashIndex].count = 1;
            return;
        }
    newnode->next = (symbolTable[hashIndex].head);
    symbolTable[hashIndex].head = newnode;
    symbolTable[hashIndex].count++;
    eleCount++;
}

void display(int size)
{
    struct node *myNode;
    int i;
    for (i = 0; i < size; i++)
    {

        if (symbolTable[i].head != NULL)
        {
            myNode = symbolTable[i].head;
            printf("\nData at index %d in Symbol Table:\nCount: %i\n", i,symbolTable[i].count);
            printf("String                 Scope\n");
            printf("-----------------------------\n");
            while (myNode != NULL)
            {
                printf("%-25s", myNode->string);
                printf("%i\n", myNode->scope);
                myNode = myNode->next;
            }
        }

    }
    return;
}

#endif