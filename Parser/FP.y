%{

%}
%token identifier integer float character_string Boolean
%%
program: 
    "{" "Program" program_name function_definitions statements "}"
    ;
program_name: 
    identifier
    ;
function_definitions: 
    (function_definition)*
    ;
function_definition:
    "{" "Function" function_name arguments statements "return" return_arg "}"
    ;
function_name: 
    identifier
    ;
arguments: 
    (argument)*
    ;
argument: 
    identifier
    ;
return_arg: 
    identifier 
    |
    ;
statements: 
    (statement)+
    ;
statement: 
    assignment_stmt 
    | function_call 
    | if_stmt 
    | while_stmt
    ;
assignment_stmt: 
    "{" "=" identifier parameter "}"
    ;
function_call: 
    "{" function_name parameters "}" 
    | "{" predefined_function parameters "}"
    ;
predefined_function: 
    "+" 
    | "_" 
    | "*" 
    | "/" 
    | "%" 
    | "print"
    ;
parameters: 
    (parameter)*
    ;
parameter: 
    function_call 
    | identifier 
    | number 
    | character_string 
    | Boolean
    ;
number: 
    integer 
    | float
    ;
if_stmt: 
    "{" "if" expression "then" statements "else" statements "}"
    ;
while_stmt: 
    "{" "while" expression "do" statements "}"
    ;
expression: 
    "{"comparison_operator parameter parameter "}" 
    | "{"Boolean_operator expression expression "}" 
    | Boolean
    ;
comparison_operator: 
    "==" 
    | ">" 
    | "<" 
    | ">=" 
    | "<=" 
    | "!="
    ;
Boolean_operator: 
    "or" 
    | "and"
    ;
%%
void main()
{
    extern FILE *yyin;
    do {
        yyparse();
    } while(!feof(yyin));
}
yyerror(char *s)
{
    /* Don't have to do anything! */
}