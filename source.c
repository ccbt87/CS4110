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
    int lines = 0;
    int prime = 13; // default prime
    int scope = 0;
    int index = 0;    
    char c;
    
    fp = fopen("test.txt", "r");  
    
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
        prime = lines * 2;
        for(; ; prime--)
        {
            if(isPrime(prime))
                break;
        }
    }
    struct hash symbolTable = {NULL, 0, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct stack activeBlock = {0, NULL, create, push, pop, peek, list, printStack};
    activeBlock.create();
    struct node* myNode;
    symbolTable.setSize(prime);     // set the symbol table size to i
    char string[1024];
    while(fscanf(fp,"%s", string)>0)
    {
        if(DEBUG){printf("Read %s, ", string);}
        if(strcmp(string, "{") == 0)
        {
            activeBlock.push(scope);
            if(DEBUG){printf("Scope %d pushed\n", scope);}
            scope++;
        }
        else if(strcmp(string, "}") == 0)
        {
            int scope = activeBlock.pop();
            if(DEBUG){printf("Scope %d poped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string); // 
            if(DEBUG){printf("Index %d, ", index);}
            if((myNode = symbolTable.findInScope(string, activeBlock.peek(), index)) == NULL)   // find in current scope
            {   // not found in currect scope
                if(DEBUG){printf("not found in currect scope, ");}
                if((myNode = symbolTable.findInGlobal(string, activeBlock.list(), index)) == NULL)  // find in global scopes
                {   // not found in global scope
                    if(DEBUG){printf("not found in global scope, ");}
                    symbolTable.insertToHash(string, activeBlock.peek(), index); // insert identifer to symbol table with currect scope #
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
        //symbolTable.display();
        activeBlock.printStack("Active Block");
        //string = malloc(256);
    }
    fclose(fp);
    symbolTable.display(); // display the symbol table
    activeBlock.printStack("Active Block"); // display the active block # stack
    //free(string);
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