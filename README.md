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
* Get size of input file
* Determine the prime
* Count the scope number

## Assumptions
* '{' indicates scope open
* '}' indicates scope close
* For every '}' there must be a '{'
* White space is the delimiter
* Identifers can be anything other than '{' , '}' or any kind of white space

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
Data at index 3 in Symbol Table:
Scope       String
------------------
1           x

Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           c
```
### Case 2
x in local
#### Input
```
{ { a b c } { x x } }
```
#### Output
```
Data at index 3 in Symbol Table:
Scope       String
------------------
2           x

Data at index 6 in Symbol Table:
Scope       String
------------------
1           a

Data at index 7 in Symbol Table:
Scope       String
------------------
1           b

Data at index 8 in Symbol Table:
Scope       String
------------------
1           c
```
### Case 3
no x in local, but x in open scope
#### Input
```
{ a b c x { x } }
```
#### Output
```
Data at index 3 in Symbol Table:
Scope       String
------------------
0           x

Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           c
```
### Case 4
no x in local, but x in closed scope
#### Input
```
{ a b c x } { x }
```
#### Output
```
Data at index 3 in Symbol Table:
Scope       String
------------------
1           x
0           x

Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           c
```
### Case 5
Not all scopes will be closed to show Active Blocks.
#### Input
```
{ a A b B { X { a A } { b B c } { F a A c C 
{ a ab ba abbab ab ba 
{ ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA  
ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ }
{ a ab ba AB BA AB BA ab ba { a ab AB Y }
a ab ba AB BA AABB } { a ba cd dc
```
#### Output
```
Data at index 1 in Symbol Table:
Scope       String
------------------
9           dc
9           cd

Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Data at index 3 in Symbol Table:
Scope       String
------------------
0           b

Data at index 4 in Symbol Table:
Scope       String
------------------
4           c
3           c

Data at index 6 in Symbol Table:
Scope       String
------------------
5           ba
5           ab

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Data at index 10 in Symbol Table:
Scope       String
------------------
4           C

Data at index 12 in Symbol Table:
Scope       String
------------------
6           AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
8           Y
6           ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
5           abbab
4           F

Data at index 15 in Symbol Table:
Scope       String
------------------
7           BA
7           AB

Data at index 16 in Symbol Table:
Scope       String
------------------
7           AABB
Active Block Contents
Block ID: 9
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0
```
