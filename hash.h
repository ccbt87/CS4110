#ifndef HEADER_FILE
#define HEADER_FILE

#include "stdlib.h"

struct hash *symbolTable = NULL;
int eleCount = 0;

long long hash(char* string, int size);
void insertToHash(char *string, int scope, int size);
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
    void (*insertToHash)(char*, int, int);
    void (*display)(int);
    void (*setSize)(int);
    int (*getSize)();
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
  }

long long hash(char* string, int size)
{
    long long key;

	for (key = 1; *string;)
	{
		key = (key*(*string++)) % size;
	}
	return (key < 0 ? -key : key);
}

void setSize(int size)
{
   symbolTable = (struct hash *)calloc(size, sizeof (struct hash));
}


 void insertToHash(char *string, int scope, int size)
{
    long long hashIndex = hash(string,size);
    struct node *newnode =  createNode(string, scope);
    struct node *myNode;
    if (!symbolTable[hashIndex].head)
        {
            symbolTable[hashIndex].head = newnode;
            symbolTable[hashIndex].count = 1;
            return;
        }
    myNode = symbolTable[hashIndex].head;
    while(myNode != NULL)
    {
        if((strcmp(myNode->string, newnode->string) == 0) && (myNode->scope == newnode->scope))
        {
            return;
        }
        myNode = myNode->next;
    }
    newnode->next = (symbolTable[hashIndex].head);
    symbolTable[hashIndex].head = newnode;
    symbolTable[hashIndex].count++;
    eleCount++;
    return;
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
