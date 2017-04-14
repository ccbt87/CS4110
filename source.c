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
    int lines = 0;
    int i, scope = 0;
    long long index = 0;
    char c;
    char* string = malloc(256);
    fp = fopen("text.txt", "r");
    while((c = fgetc(fp)) != EOF)
    {
        if(c == '\n')
        {
            lines++;
        }
    }
    rewind(fp);
    if(lines > 17)
    {
        i = lines;
        for(; ; i--)
        {
            if(prime(i))
                break;
        }
    }
    else
    {
        i = 13;
    }

    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct stack activeBlock = {NULL, push, pop, printStack, create, peek};
    activeBlock.create(1);
    struct node* myNode;
    symbolTable.setSize(i);
     activeBlock.push(scope);
            if(DEBUG){printf("Scope %d pushed\n", scope);}
            scope++;
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
            if(DEBUG){printf("Index %lld\n", index);}

            if((myNode = symbolTable.findInScope(string, activeBlock.peek() , index)) == NULL)
            {
                if((myNode = symbolTable.findInGlobal(string, activeBlock, index)) == NULL)
                {
                    symbolTable.insertToHash(string, activeBlock.peek(), index);
                }
                //else
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
