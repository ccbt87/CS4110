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

## Components and Functions
### hash.h - One symbol table
* Important routines: findInScope(), findInGlobal(), insertToHash(), display()
* Maintain scope info with the identifier in the symbol table
* Dynamic allocation of space for id names
* Store scope number with id names
* Optimized hash function
* Chained Hash Table
### stack.h - Active scope number stack
* Store scope numbers that are still open
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
* Since the test inputs don't contain the information that indicate whether a identifer is a declaration or not, the program assume:
    1. If the identifer already exists in current or open scopes, it's not a declaration and will not be added to the Symbol Table.
    2. If the identifer doesn't exist in current and open scopes, it's a declaration and will be added to the Symbol Table.

## Compile and Run
Put hash.h, stack.h, source.c and testinput files in the same directory 
### Under Linux
Launch a Terminal, navigate to the directory that contains the files discribed above, execute following command
```
gcc source.c -o source
```
Execute the program
```
./source
```
### Under Windows
Put hash.h, stack.h, source.c and testinput files in the same directory. 
Open CodeBlocks IDE. Create new empty project. 
Pick project name and location of project folder (example: Desktop). Use GNU GCC Compiler with default options. 
Copy and paste hash.h, stack.h, source.c and testinput files into the CodeBlocks project folder (example: Desktop/ProjectName/) created in previous step.
Go back to CodeBlocks. In left side bar under tab "Projects", right-click project name and click "Add Files Recursively" click OK, OK, OK with default options.
Under "Build" menu click "Build", then also under "Build" menu click "Run", or just use "Build" and "Run" buttons on toolbar.

## Test
To switch to another input file, go to line 19 in the source.h file, change the file name and save.
```
fp = fopen("testinput1.txt", "r");
```
The debug mode will print more detailed information.
To turn on the debug mode, go to line 7 in the source.h file, set DEBUG to 1 and save.
```
#define DEBUG 1
```
To turn off the debug mode, go to line 7 in the source.h file, set DEBUG to 0 and save.
```
#define DEBUG 0
```
### Case 1 - There's no 'x' in local or open scopes, and read in a 'x'
#### Input
```
{ a b c { x } }
```
#### Output
```
Prime: 13

Read {, Scope 0 pushed.
Active Block Contents
Block ID: 0

Read a, hashkey 6, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Read b, hashkey 7, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Read c, hashkey 8, not found in currect, not found in global, insert to ST.
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

Read {, Scope 1 pushed.
Active Block Contents
Block ID: 1
Block ID: 0

Read x, hashkey 3, not found in currect, not found in global, insert to ST.
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

Read }, Scope 1 popped.
Active Block Contents
Block ID: 0

Read }, Scope 0 popped.
Active Block Contents nothing


========= Finished reading the input file =========

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

Active Block Contents nothing
```
### Case 2 - There's a 'x' in local, and read in a 'x'
#### Input
```
{ { a b c } { x x } }
```
#### Output
```
Prime: 13

Read {, Scope 0 pushed.
Active Block Contents
Block ID: 0

Read {, Scope 1 pushed.
Active Block Contents
Block ID: 1
Block ID: 0

Read a, hashkey 6, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
1           a

Read b, hashkey 7, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
1           a

Data at index 7 in Symbol Table:
Scope       String
------------------
1           b

Read c, hashkey 8, not found in currect, not found in global, insert to ST.
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

Read }, Scope 1 popped.
Active Block Contents
Block ID: 0

Read {, Scope 2 pushed.
Active Block Contents
Block ID: 2
Block ID: 0

Read x, hashkey 3, not found in currect, not found in global, insert to ST.
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

Read x, hashkey 3, found in current scope 2, won't insert.
Read }, Scope 2 popped.
Active Block Contents
Block ID: 0

Read }, Scope 0 popped.
Active Block Contents nothing


========= Finished reading the input file =========

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

Active Block Contents nothing
```
### Case 3 - There's no 'x' in local, but there's a 'x' in open scope, and read in a 'x'
#### Input
```
{ a b c x { x } }
```
#### Output
```
Prime: 13

Read {, Scope 0 pushed.
Active Block Contents
Block ID: 0

Read a, hashkey 6, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Read b, hashkey 7, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Read c, hashkey 8, not found in currect, not found in global, insert to ST.
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

Read x, hashkey 3, not found in currect, not found in global, insert to ST.
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

Read {, Scope 1 pushed.
Active Block Contents
Block ID: 1
Block ID: 0

Read x, hashkey 3, not found in currect, found in global scope 0, won't insert.
Read }, Scope 1 popped.
Active Block Contents
Block ID: 0

Read }, Scope 0 popped.
Active Block Contents nothing


========= Finished reading the input file =========

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

Active Block Contents nothing
```
### Case 4 - There's no 'x' in local, and there's a 'x' in closed scope, and read in a 'x'
#### Input
```
{ a b c x } { x }
```
#### Output
```
Prime: 13

Read {, Scope 0 pushed.
Active Block Contents
Block ID: 0

Read a, hashkey 6, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Read b, hashkey 7, not found in currect, not found in global, insert to ST.
Data at index 6 in Symbol Table:
Scope       String
------------------
0           a

Data at index 7 in Symbol Table:
Scope       String
------------------
0           b

Read c, hashkey 8, not found in currect, not found in global, insert to ST.
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

Read x, hashkey 3, not found in currect, not found in global, insert to ST.
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

Read }, Scope 0 popped.
Active Block Contents nothing

Read {, Scope 1 pushed.
Active Block Contents
Block ID: 1

Read x, hashkey 3, not found in currect, not found in global, insert to ST.
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

Read }, Scope 1 popped.
Active Block Contents nothing


========= Finished reading the input file =========

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

Active Block Contents nothing
```
### Case 5 - Not all scopes will be closed to show Active Blocks.
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
Prime: 19

Read {, Scope 0 pushed.
Active Block Contents
Block ID: 0

Read a, hashkey 2, not found in currect, not found in global, insert to ST.
Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Read A, hashkey 8, not found in currect, not found in global, insert to ST.
Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Read b, hashkey 3, not found in currect, not found in global, insert to ST.
Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Data at index 3 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Read B, hashkey 9, not found in currect, not found in global, insert to ST.
Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Data at index 3 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Read {, Scope 1 pushed.
Active Block Contents
Block ID: 1
Block ID: 0

Read X, hashkey 12, not found in currect, not found in global, insert to ST.
Data at index 2 in Symbol Table:
Scope       String
------------------
0           a

Data at index 3 in Symbol Table:
Scope       String
------------------
0           b

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Data at index 12 in Symbol Table:
Scope       String
------------------
1           X

Read {, Scope 2 pushed.
Active Block Contents
Block ID: 2
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read A, hashkey 8, not found in currect, found in global scope 0, won't insert.
Read }, Scope 2 popped.
Active Block Contents
Block ID: 1
Block ID: 0

Read {, Scope 3 pushed.
Active Block Contents
Block ID: 3
Block ID: 1
Block ID: 0

Read b, hashkey 3, not found in currect, found in global scope 0, won't insert.
Read B, hashkey 9, not found in currect, found in global scope 0, won't insert.
Read c, hashkey 4, not found in currect, not found in global, insert to ST.
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
3           c

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Data at index 12 in Symbol Table:
Scope       String
------------------
1           X

Read }, Scope 3 popped.
Active Block Contents
Block ID: 1
Block ID: 0

Read {, Scope 4 pushed.
Active Block Contents
Block ID: 4
Block ID: 1
Block ID: 0

Read F, hashkey 13, not found in currect, not found in global, insert to ST.
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
3           c

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Data at index 12 in Symbol Table:
Scope       String
------------------
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
4           F

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read A, hashkey 8, not found in currect, found in global scope 0, won't insert.
Read c, hashkey 4, not found in currect, not found in global, insert to ST.
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

Data at index 8 in Symbol Table:
Scope       String
------------------
0           A

Data at index 9 in Symbol Table:
Scope       String
------------------
0           B

Data at index 12 in Symbol Table:
Scope       String
------------------
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
4           F

Read C, hashkey 10, not found in currect, not found in global, insert to ST.
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
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
4           F

Read {, Scope 5 pushed.
Active Block Contents
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read ab, hashkey 6, not found in currect, not found in global, insert to ST.
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
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
4           F

Read ba, hashkey 6, not found in currect, not found in global, insert to ST.
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
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
4           F

Read abbab, hashkey 13, not found in currect, not found in global, insert to ST.
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
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
5           abbab
4           F

Read ab, hashkey 6, found in current scope 5, won't insert.
Read ba, hashkey 6, found in current scope 5, won't insert.
Read {, Scope 6 pushed.
Active Block Contents
Block ID: 6
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ, hashkey 13, not found in currect, not found in global, insert to ST.
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
1           X

Data at index 13 in Symbol Table:
Scope       String
------------------
6           ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
5           abbab
4           F

Read AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA, hashkey 12, not found in currect, not found in global, insert to ST.
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
6           ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
5           abbab
4           F

Read ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ, hashkey 13, found in current scope 6, won't insert.
Read }, Scope 6 popped.
Active Block Contents
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read {, Scope 7 pushed.
Active Block Contents
Block ID: 7
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read ab, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read ba, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read AB, hashkey 15, not found in currect, not found in global, insert to ST.
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
6           ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
5           abbab
4           F

Data at index 15 in Symbol Table:
Scope       String
------------------
7           AB

Read BA, hashkey 15, not found in currect, not found in global, insert to ST.
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
6           ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
5           abbab
4           F

Data at index 15 in Symbol Table:
Scope       String
------------------
7           BA
7           AB

Read AB, hashkey 15, found in current scope 7, won't insert.
Read BA, hashkey 15, found in current scope 7, won't insert.
Read ab, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read ba, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read {, Scope 8 pushed.
Active Block Contents
Block ID: 8
Block ID: 7
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read ab, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read AB, hashkey 15, not found in currect, found in global scope 7, won't insert.
Read Y, hashkey 13, not found in currect, not found in global, insert to ST.
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

Read }, Scope 8 popped.
Active Block Contents
Block ID: 7
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read ab, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read ba, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read AB, hashkey 15, found in current scope 7, won't insert.
Read BA, hashkey 15, found in current scope 7, won't insert.
Read AABB, hashkey 16, not found in currect, not found in global, insert to ST.
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

Read }, Scope 7 popped.
Active Block Contents
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read {, Scope 9 pushed.
Active Block Contents
Block ID: 9
Block ID: 5
Block ID: 4
Block ID: 1
Block ID: 0

Read a, hashkey 2, not found in currect, found in global scope 0, won't insert.
Read ba, hashkey 6, not found in currect, found in global scope 5, won't insert.
Read cd, hashkey 1, not found in currect, not found in global, insert to ST.
Data at index 1 in Symbol Table:
Scope       String
------------------
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

Read dc, hashkey 1, not found in currect, not found in global, insert to ST.
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


========= Finished reading the input file =========

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
