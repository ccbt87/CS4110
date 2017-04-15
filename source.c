#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "Stack.h"

#define DEBUG 1

int isPrime(int p);

int main()
{
    FILE *fp;
    long int size = 0;
    int prime = 0;
    int scope = 0;
    int index = 0;    
    
    fp = fopen("test.txt", "r");
    fseek(fp, 1, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    if(size > 271)
    {
        size /= 16;   
        printf("%li size\n", size);
        prime = size -1;
        for(; ; prime--)
        {
            if(isPrime(prime))
                break;
        }
    }    
    else
    {
        prime = 13;
    }
    
    struct hash symbolTable = {NULL, 0, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct stack activeBlock = {NULL, push, pop, printStack, create, peek};
    activeBlock.create();
    struct node* myNode;
    symbolTable.setSize(prime); // set the symbol table size to prime
    
    char string[256]; // buffer to read in string from a file
    while(fscanf(fp,"%s", string)>0)
    {
        if(DEBUG){printf("Read %s, ", string);}
        if(strcmp(string, "{") == 0)
        {
            activeBlock.push(scope);
            if(DEBUG){printf("Scope %d pushed", scope);}
            scope++;
        }
        else if(strcmp(string, "}") == 0)
        {
            int scope = activeBlock.pop();
            if(DEBUG){printf("Scope %d poped", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string); // 
            if(DEBUG){printf("Index %d, ", index);}
            if((myNode = symbolTable.findInScope(string, activeBlock.peek(), index)) == NULL)   // find in current scope
            {   // not found in currect scope
                if(DEBUG){printf("not found in currect scope, ");}
                if((myNode = symbolTable.findInGlobal(string, activeBlock, index)) == NULL)  // find in global scopes
                {   // not found in global scope
                    if(DEBUG){printf("not found in global scope, ");}
                    symbolTable.insertToHash(string, activeBlock.peek(), index); // insert identifer to symbol table with currect scope #
                    if(DEBUG){printf("inserted to symbol table");}
                }
                else
                {
                    // found in global scope
                    if(DEBUG){printf("found in global scope");}
                }
            } 
            else
            {
                // found in current scope
                if(DEBUG){printf("found in current scope");}
            }
        }
        if(DEBUG){printf("\n");}
        //symbolTable.display();
        activeBlock.printStack("Active Block");
    }
    fclose(fp);
    symbolTable.display(); // display the symbol table
    activeBlock.printStack("Active Block"); // display the active block # stack
    return 0;
}

// check for prime numbers
int isPrime(int p)
{
    int i;
    for(i = 2; p%i != 0; i++);

    if(p==i)
        return 1;
    else
        return 0;

}
