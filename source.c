#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "stack.h"

#define DEBUG 1

int isPrime(int p);

int main()
{
    FILE *fp;
    long int size;
    int prime, scope = 0;
    int first = 1;
    long long index = 0;
    char string[256]; // buffer to read in string from a file
    fp = fopen("testinput1.txt", "r"); // specify input file name here
    fseek(fp, 1, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    
    // determine the prime based on file size
    if(size > 271)
    {
        size /= 16;
        prime = size -1;
        for(; ; prime--)
        {
            if(isPrime(prime))
            break;
        }
    }
    else
        prime = 13; // default prime for file size smaller than 272
    if(DEBUG) {printf("Prime: %d\n\n", prime);}
    
    struct Hash symbolTable = {NULL, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
    struct Stack activeBlock = {NULL, push, pop, printStack, peek};
    struct node* myNode;
    symbolTable.head = symbolTable.setSize(symbolTable.head, prime); // set the symbol table size to prime

    while(fscanf(fp,"%s", string)>0)
    {
        if(DEBUG){printf("Read %s, ", string);}
        // deal with the GLOBAL variables if the test input is not starts with a '{'
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
        
        if(strcmp(string, "{") == 0)
        {
            activeBlock.head = activeBlock.push(activeBlock.head, scope);
            if(DEBUG)
            {
                printf("Scope %d pushed.\n", scope);
                activeBlock.printStack(activeBlock.head, "Active Block");
                printf("\n");
            }
            scope++;
        }
        else if(strcmp(string, "}") == 0)
        {
            int scope = activeBlock.peek(activeBlock.head);
            activeBlock.head = activeBlock.pop(activeBlock.head);
            if(DEBUG)
            {
                printf("Scope %d popped.\n", scope);
                activeBlock.printStack(activeBlock.head, "Active Block");
                printf("\n");
            }
        }
        else
        {
            index = symbolTable.hashkey(string, prime);
            if(DEBUG){printf("hashkey %lli, ", index);}

            if((myNode = symbolTable.findInScope(symbolTable.head, string, activeBlock.peek(activeBlock.head) , index)) == NULL)
            {
                // not found in currect scope
                if(DEBUG){printf("not found in currect, ");}
                if((myNode = symbolTable.findInGlobal(symbolTable.head, activeBlock.head, string, index)) == NULL)
                {
                    // not found in global scope
                    symbolTable.insertToHash(symbolTable.head, string, activeBlock.peek(activeBlock.head), index);
                    if(DEBUG)
                    {
                        printf("not found in global, ");
                        printf("insert to ST.");
                        symbolTable.display(symbolTable.head, prime); 
                        printf("\n");
                    }
                }
                else
                {
                    // found in global scope
                    if(DEBUG){printf("found in global scope %d, won't insert.\n", myNode->scope);}
                }
            }
            else
            {
                // found in current scope
                if(DEBUG){printf("found in current scope %d, won't insert.\n", activeBlock.peek(activeBlock.head));}
            }
        }
    }
    fclose(fp);
    printf("\n========= Finished reading the input file =========\n");
    symbolTable.display(symbolTable.head, prime); // display the symbol table
    printf("\n");
    activeBlock.printStack(activeBlock.head, "Active Block"); // display the active block # stack
    return 0;
}

//check for prime numbers
int isPrime(int p)
{
    int i;
    for(i = 2; p%i != 0; i++);
    if(p==i)
        return 1;
    else
        return 0;
}
