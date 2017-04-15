#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "Stack.h"

int prime(int p);
#define DEBUG 1

int main()
{
    FILE *fp;
    long int size;
    int i, scope = 0;
    long long index = 0;
    char* string = malloc(sizeof(string));
    fp = fopen("bible.txt", "r");
    fseek(fp, 1, SEEK_END);
    size = ftell(fp);
    if(size > 271)
    {
        size /= 16;
        if(DEBUG) {printf("%li size\n", size);}
        i = size -1;
        for(; ; i--)
        {
            if(prime(i))
            break;
        }
    }
    else
        i = 13;
    if (DEBUG) {printf("Actual size %i\n", i);}

    rewind(fp);
    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct stack activeBlock = {NULL, push, pop, printStack, peek};
    struct node* myNode;
    symbolTable.head = symbolTable.setSize(symbolTable.head, i);

    //symbolTable = malloc(sizeof(struct hash*));
   /*symbolTable.head = malloc(sizeof(struct node **)*i);
    for(i = i-1; i >= 0; i--)
    {
        symbolTable.head[i] = NULL;//malloc(sizeof(struct node*));
        //symbolTable.head[i]->scope = -1;
        //printf(" this address %p\n", symbolTable->head[i]);
         printf(" or address %p\n", &symbolTable.head[i]);
    }*/


     activeBlock.head = activeBlock.push(activeBlock.head, scope);
            if(DEBUG){printf("Scope %d pushed\n", scope);}
            scope++;
    while(fscanf(fp,"%s", string)>0)
    {
       if(DEBUG) {printf("string %s action ", string);}
         if(DEBUG){printf("Read %s\n", string);}
        if(strcmp(string, "{") == 0)
        {
            activeBlock.head = activeBlock.push(activeBlock.head, scope);
            if(DEBUG){printf("Scope %d pushed\n", scope);}
            scope++;
        }
        else if(strcmp(string, "}") == 0)
        {
            int scope = activeBlock.pop(activeBlock.head);
            if(DEBUG){printf("Scope %d popped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string, i);
            if(DEBUG){printf("Index %li\n", index);}
            //printf(" or address %p\n", &symbolTable.head[index]);
            if((myNode = symbolTable.findInScope(symbolTable.head, string, activeBlock.peek(activeBlock.head) , index)) == NULL)
            {
                if((myNode = symbolTable.findInGlobal(symbolTable.head, activeBlock.head, string, index)) == NULL)
                {
                    if(DEBUG) {printf("insert\n");}
                    symbolTable.insertToHash(symbolTable.head, string, activeBlock.peek(activeBlock.head), index);
                }
                else
                {
                   if(DEBUG) {printf("Found in Global\n");}
                    // found in global scope
                }
            }
            else
            {
               if(DEBUG) {printf("Found in Local\n");}
                // found in current scope
            }
        }
        string = malloc(sizeof(string));
    }
    symbolTable.display(symbolTable.head, i);
    activeBlock.printStack(activeBlock.head, "Active Block");
    system("pause");
   free(string);
   return 0;
}

//check for prime numbers
int prime(int p)
{
    int i;
    for(i = 2; p%i != 0; i++);

        if(p==i)
            return 1;
        else
            return 0;

}
