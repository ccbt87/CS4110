%option noyywrap
%{
#include <math.h>
#include "stack.h"
#include "hash.h"
#include "y.tab.h"

#define DEBUG 0

int isPrime(int p);
void buildST(char* string, char* type);

struct Hash symbolTable = {NULL, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
struct Stack activeBlock = {NULL, push, pop, printStack, peek};
struct node* myNode;
int prime, scope = 0;
long long key = 0;
%}
/* 1.2 identifier, integer, float, character-string, Boolean */
ID          [a-zA-Z][a-zA-Z0-9]{0,5}
INT         (\-?[ \t\n]?[1-9][0-9]*)|0
FLOAT       (((\-?[ \t\n]?[1-9][0-9]*)|0)\.[0-9]+)|(\-[ \t\n]?0\.[0-9]*[1-9])
STRING      \([ a-zA-Z0-9\\]+\)
BOOLEAN     T|F
UNDEFINED   [a-zA-Z0-9]*|[^A-Za-z0-9\{|\}|\(|\)|\=|\+|\-|\*|\/|\%|\=\=|\>|\<|\>\=|\<\=|\!\= \t\n]*[a-zA-Z0-9]*|.
/* 1.4 White Space */
SPACE       [ \t\r\n]+
/* keywords and special symbols */
KEYWORD     Program|Function|return|if|then|else|while|do|or|and|print
SYMBOL      \{|\}|\(|\)|\=|\+|\-|\*|\/|\%|\=\=|\>|\<|\>\=|\<\=|\!\=
%%
{INT}       printf("Integer: %d\n", atoi(yytext)), buildST(yytext, "Integer");
{FLOAT}     printf("Float: %f\n", atof(yytext)), buildST(yytext, "Float");
{KEYWORD}   printf("Keyword: %s\n", yytext), buildST(yytext, "Keyword");
{BOOLEAN}   printf("Boolean: %s\n", yytext), buildST(yytext, "Boolean");
{ID}        printf("Identifier: %s\n", yytext), buildST(yytext, "Identifier");
{STRING}    printf("Char-String: %s\n", yytext), buildST(yytext, "String");
{SYMBOL}    printf("Special Symbol: %s\n", yytext), buildST(yytext, "Special Symbol");
{SPACE}     /* skip whitespace */
{UNDEFINED} printf("Unrecognized: %s\n",yytext);
%%
void main()
{
    // determine the prime based on file size
    FILE *fp = stdin;
    long int size;
    fseek(fp, 1, SEEK_END);
    size = ftell(fp);
    rewind(fp);
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
    
    symbolTable.head = symbolTable.setSize(symbolTable.head, prime);
    yylex();
    fclose(fp);
    printf("\n========= Finished reading the input file =========\n");
	symbolTable.display(symbolTable.head, prime);  
    printf("\n");    
    activeBlock.printStack(activeBlock.head, "Active Block");
} 

void buildST(char* string, char* type)
{    
    if(DEBUG){printf("Read %s, ", string);}      
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
        key = symbolTable.hashkey(string, prime);
        if(DEBUG){printf("hashkey %lli, ", key);}

        if((myNode = symbolTable.findInScope(symbolTable.head, string, activeBlock.peek(activeBlock.head) , key)) == NULL)
        {
            // not found in current scope
            if(DEBUG){printf("not found in current, ");}
            if((myNode = symbolTable.findInGlobal(symbolTable.head, activeBlock.head, string, key)) == NULL)
            {
                // not found in global scope
                symbolTable.insertToHash(symbolTable.head, string, type, activeBlock.peek(activeBlock.head), key);
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
                //if(DEBUG){printf("found in global scope %d, won't insert.\n", myNode->scope);}
            }
        }
        else
        {
            // found in current scope
            //if(DEBUG){printf("found in current scope %d, won't insert.\n", activeBlock.peek(activeBlock.head));}
        }
    }
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