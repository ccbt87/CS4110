#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "hash.h"

int prime(int p);

int main()
{
    FILE *fp;
    long int size;
    int i, scope = 0;
    char* string = malloc(256);
    fp = fopen("Source.cpp", "r");
    fseek(fp, 1, SEEK_END);
   size = ftell(fp)/16;
    printf("%i size\n", size);
    i = size -1;
    for(i; ; i--)
    {
        if(prime(i))
            break;
    }
    rewind(fp);
    struct hash symbolTable = {NULL, 0, insertToHash, display, setSize};
    symbolTable.setSize(i);
    while(fscanf(fp,"%s", string)>0)
    {
        if(strcmp(string, "{") == 0)
            scope++;
        else if(strcmp(string, "}") == 0)
            scope--;
        else
            symbolTable.insertToHash(string, scope, i);
        string = malloc(256);
    }
    symbolTable.display(i);
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
