#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "Stack.h"

int prime(int p);
#define DEBUG 0

int main()
{
    FILE *fp;
    long int size;
    int i, scope = 0;
    long long index = 0;
    char* string = malloc(256);
    fp = fopen("test.txt", "r");
    fseek(fp, 1, SEEK_END);
    if(size > 271)
    {
        size /= 16;
    }

    printf("%li size\n", size);
    i = size -1;
    for(; ; i--)
    {
        if(prime(i))
            break;
    }
    rewind(fp);
    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct stack activeBlock = {0, NULL, push, pop, printStack, create}, peek;
    //struct stack inactiveBlock = {0, NULL, push, pop, printStack, create};
    activeBlock.create(i);
    struct node* myNode;
    symbolTable.setSize(i);
    while(fscanf(fp,"%s", string)>0)
    {
         if(DEBUG){printf("Read %s\n", string);}
        if(strcmp(string, "{") == 0)
        {
            activeBlock.push(scope);
            if(DEBUG){printf("Scope %d pushed\n", scope);}
            scope++;
        }
        else if(strcmp(string, "}") == 0)
        {
            int scope = activeBlock.pop();
            if(DEBUG){printf("Scope %d popped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string, i);
            if(DEBUG){printf("Index %d\n", index);}
            if((myNode = symbolTable.findInScope(string, activeBlock.peek(), index)) == NULL)
            {
                if((myNode = symbolTable.findInGlobal(string, activeBlock.size(), index)) == NULL)
                {
                    symbolTable.insertToHash(string, activeBlock.peek(), i, index);
                }
                else
                {
                    // found in global scope
                }
            }
            else
            {
                // found in current scope
            }
        }
        string = malloc(256);
    }
    symbolTable.display(i);
    activeBlock.printStack("Active Block");

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
