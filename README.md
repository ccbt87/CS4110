# Project 0 - Symbol Table
## Team Members
Robert M.
Jon Q.
Hongjie Z.
## Environment
```
Language: C
OS: Ubuntu 16.10
IDE/Editor: Code::Blocks, Notepad++ v7, VIM 7.4.1829
Compiler: gcc 6.2.0
```
## Structures
### hash.h - One symbol table
* Important routines: findInScope(), findInGlobal(), insertToHash(), display()
* Maintain scope info with the identifier in the symbol table
* Dynamic allocation of space for id names
* Optimized hash function
* Chained Hash Table
### stack.h - Active scope number stack
* Current scope is on the top of the stack 
### source.c - Driver program
* Read input from file
* Determine the prime
* Count the scope number
*
## Assumptions
* Valid input will always starts with a '{' which indicates scope open
* Space is the delimiter
* Identifers can be anything other than '{' , '}' or space
* 

## Compile and Run
### Under Linux
Launch a Terminal, execute following command
```
gcc source.c -o source
```
Execute
```
./source
```
### Under Windows
## Test
### Case 1
no x anywhere
#### Input
```
{ a b c { x } }
```
#### Output
```

```
### Case 2
x in local
#### Input
```
{ a b c } x x } }
```
#### Output
```

```
### Case 3
no x in local, but x in open scope
#### Input
```
{ a b c x { x } }
```
#### Output
```

```
### Case 4
no x in local, but x in closed scope
#### Input
```
{ a b c x } { x }
```
#### Output
```

```
