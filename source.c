#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "Stack.h"

#define DEBUG 0

int prime(int p);

int main()
{
    FILE *fp;
    long int size;
    int i = 13; // default prime
    int scope = 0;
    int index = 0;
    char* string = malloc(256);
    fp = fopen("test.txt", "r");
    
    fseek(fp, 1, SEEK_END);
    size = ftell(fp);
    if(size > 271)
    {
        size /= 16;   
        printf("%li size\n", size);
        i = size -1;
        for(; ; i--)
        {
            if(prime(i))
                break;
        }
    }
    rewind(fp);
    
    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct block activeBlock = {0, NULL, push, pop, peek, list, printStack};
    //struct block inactiveBlock = {0, NULL, push, pop, peek, printStack};
    struct node* myNode;
    symbolTable.setSize(i);     // set the symbol table size to i
    activeBlock.push(scope);    // push the global scope #0
    scope++;    // normal scopes start from #1
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
            if(DEBUG){printf("Scope %d poped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string, i); // 
            if(DEBUG){printf("Index %d\n", index);}
            if((myNode = symbolTable.findInScope(string, activeBlock.peek(), index)) == NULL)   // find in current scope
            {   // not found in currect scope
                if((myNode = symbolTable.findInGlobal(string, activeBlock.list(), index)) == NULL)  // find in global scopes
                {   // not found in global scope
                    symbolTable.insertToHash(string, activeBlock.peek(), i, index); // insert identifer to symbol table with currect scope #
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
        //symbolTable.display(i);
        activeBlock.printStack("Active Block");
        string = malloc(256);
    }
    activeBlock.pop();  // pop the global scope #0
    symbolTable.display(i); // display the symbol table
    activeBlock.printStack("Active Block"); // display the active block # stack
    //inactiveBlock.printStack("InActive Block");
    //system("pause");
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
