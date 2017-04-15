#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "stack.h"

int prime(int p);
#define DEBUG 0

int main()
{
    FILE *fp;
    long int size;
    int i, scope = 0;
    int first = 1;
    long long index = 0;
    char string[256];
    fp = fopen("test.txt", "r");
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
    struct Hash symbolTable = {NULL, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct Stack activeBlock = {NULL, push, pop, printStack, peek};
    struct node* myNode;
    symbolTable.head = symbolTable.setSize(symbolTable.head, i);

    while(fscanf(fp,"%s", string)>0)
    {
        if(first == 1)
        {
            if(strcmp(string, "{") != 0)
                {
                    activeBlock.head = activeBlock.push(activeBlock.head, scope);
                    if(DEBUG){printf("Scope %d pushed\n", scope);}
                    scope++;
                }
            first = 0;
        }

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
            int scope = activeBlock.peek(activeBlock.head);
            activeBlock.head = activeBlock.pop(activeBlock.head);
            if(DEBUG){printf("Scope %d popped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string, i);
            if(DEBUG){printf("Index %lli\n", index);}

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
    }
    symbolTable.display(symbolTable.head, i);
    activeBlock.printStack(activeBlock.head, "Active Block");
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
