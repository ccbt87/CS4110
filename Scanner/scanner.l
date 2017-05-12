%option noyywrap
%{
#include <math.h>
#include "stack.h"
#include "hash.h"

#define DEBUG 0
int prime(int p);
void buildST(char* string, char* type);

struct Hash symbolTable = {NULL, insertToHash, display, setSize, hashkey, findInScope, findInGlobal};
struct Stack activeBlock = {NULL, push, pop, printStack, peek};
struct node* myNode;
int i, scope = 0;
long long myIndex = 0;
%}
/* 1.2 identifier, integer, float, character-string, Boolean */
ID          [a-zA-Z][a-zA-Z0-9]{0,5}
INT         (\-?[ \t\n]?[1-9][0-9]*)|0
FLOAT       (((\-?[ \t\n]?[1-9][0-9]*)|0)\.[0-9]+)|(\-[ \t\n]?0\.[1-9][0-9]*)
STRING      \([ a-zA-Z0-9\n]+\)
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
int main()
{
    FILE *fp = stdin;
    long int size;
    char string[256];
    char type[256];
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

    symbolTable.head = symbolTable.setSize(symbolTable.head, i);
	yylex(); /*not OK if actions return values */
	symbolTable.display(symbolTable.head, i);
    activeBlock.printStack(activeBlock.head, "Active Block");
	
} 

void buildST(char* string, char* type)
{
	//int i, scope = 0;
    	//int first = 1;
    	//long long index = 0;
	/*if(first == 1)
        {
            if(strcmp(string, "{") != 0)
                {
                    activeBlock.head = activeBlock.push(activeBlock.head, scope);
                    if(DEBUG){printf("Scope %d pushed\n", scope);}
                    scope++;
                }
            first = 0;
        }*/

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
            myIndex = symbolTable.hashkey(string, i);
            if(DEBUG){printf("Index %lli\n", myIndex);}

            if((myNode = symbolTable.findInScope(symbolTable.head, string, activeBlock.peek(activeBlock.head) , myIndex)) == NULL)
            {
		if(DEBUG){printf("Not in scope\n");}
                if((myNode = symbolTable.findInGlobal(symbolTable.head, activeBlock.head, string, myIndex)) == NULL)
                {
                    if(DEBUG) {printf("insert\n");}
                    symbolTable.insertToHash(symbolTable.head, string, type, activeBlock.peek(activeBlock.head), myIndex);
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

int prime(int p)
{
    int i;
    for(i = 2; p%i != 0; i++);

        if(p==i)
            return 1;
        else
            return 0;
}