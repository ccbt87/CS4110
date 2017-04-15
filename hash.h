#ifndef HEADER_HASH
#define HEADER_HASH

#include "stdlib.h"
#include "stack.h"

typedef struct
{
    char* Id;
    int scope;
    struct node* next;

}node;

typedef struct
{
    node **head;
    void (*insertToHash)(node**, char*, int, long long);
    void (*display)(node**, int);
    node** (*setSize)(node**, int);
    long long (*hashkey)(char*, int);
    node* (*findInScope)(node**, char*, int, long long);
    node* (*findInGlobal)(node**, block* , char*, long long);
}Hash;

 node * createNode(char *s, int scope)
 {
    node* newnode;
    newnode = malloc(sizeof(newnode));
    newnode->scope = scope;
    newnode->Id = malloc(strlen(s));
    strcpy(newnode->Id, s);
    newnode->next = NULL;
    return newnode;
  };

long long hashkey(char* myString, int s)
{
    long long key;

	for (key = 1; *myString;)
	{
		key = (key*(long long)(*myString++)) % s;
	}
	return (key < 0 ? -key : key);
}

struct node** setSize(struct node** h, int s)
{
   h = malloc(s * sizeof(h));
    for(s = s-1; s >= 0; s--)
    {
        h[s] = NULL;
    }
    return h;
}

node* findInScope(node** h, char* myString, int scope, long long index)
{
    node *myNode = NULL;
    if (h[index] == NULL)
    {
        free(myNode);
        return myNode;
    }
    myNode = h[index];
    while(myNode != NULL)
    {
        if((strcmp(myNode->Id, myString) == 0) && (myNode->scope == scope))
        {
            return myNode;
        }
        myNode = myNode->next;
    }
    return myNode;
}

node* findInGlobal(node** h, block* b, char* myString, long long index)//not working
{
    if (b == NULL)
    {
        return NULL;
    }
    node* myNode = NULL;
    block* myBlock = b;
    int i = 0;
    while(myBlock != NULL)
    {
        int scope = myBlock->scope;
        if ((myNode = findInScope(h, myString, scope, index)) != NULL)
        {
            return myNode;
        }
        myBlock = myBlock->next;
    }
    free(myBlock);
    return myNode;
}

 void insertToHash(node** h, char *myString, int scope, long long hashIndex)
{
    node *newnode;
    newnode =  createNode(myString, scope);

    if (!h[hashIndex])
        {
            h[hashIndex] = newnode;
            return;
        }
    newnode->next = h[hashIndex];
    h[hashIndex] = newnode;

  }

void display(node** h, int s)
{
    node *myNode;
    int i;
    for (i = 0; i < s; i++)
    {

        if (h[i])
        {
            myNode = h[i];
             printf("\nData at index %d in Symbol Table:\n", i);
            printf("String                 Scope\n");
            printf("-----------------------------\n");
            while (myNode != NULL)
            {
                printf("%-25s", myNode->Id);
                printf("%i\n", myNode->scope);
                myNode = myNode->next;
            }
        }

    }
    free(myNode);
    return;
  }

#endif
