#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"
#include "Stack.h"

int prime(int p);

int main()
{
    FILE *fp;
    long int size;
    int i = 13; 
    int scope = 0;
    int index = 0;
    char* string = malloc(256);
    fp = fopen("test.txt", "r");
    /*
    fseek(fp, 1, SEEK_END);
    size = ftell(fp)/16;
    printf("%li size\n", size);
    i = size -1;
    for(; ; i--)
    {
        if(prime(i))
            break;
    }
    rewind(fp);
    */
    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize, hashkey, findInScope};
    struct block activeBlock = {0, NULL, push, pop, peek, printStack};
    //struct block inactiveBlock = {0, NULL, push, pop, peek, printStack};
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
            int scope = activeBlock.pop();//not working correctly
            if(DEBUG){printf("Scope %d poped\n", scope);}
        }
        else
        {
            index = symbolTable.hashkey(string,i);
            if(DEBUG){printf("Index %d\n", index);}
            if((myNode = symbolTable.findInScope(string, activeBlock.peek(), index)) == NULL)
            {
                symbolTable.insertToHash(string, activeBlock.peek(), i, index);
            }          
        }
        symbolTable.display(i);
        activeBlock.printStack("Active Block");
        string = malloc(256);
    }
    //symbolTable.display(i);
    //activeBlock.printStack("Active Block");
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
