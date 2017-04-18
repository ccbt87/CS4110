# Project 0 - Symbol Table
## Team Members
Robert M.
Jon Q.
Hongjie Z.

## Environment
```
Language: C
OS: Windows 10, CentOS 6.8, Ubuntu 16.10
IDE/Editor: CodeBlocks 16.01, Notepad++ v7, VIM 7.4.1829
Compiler: gcc 4.4.7, 5.4.0, 6.2.0
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
1. Open CodeBlocks IDE. Create new empty project. 
2. Pick project name and location of project folder (example: Desktop). Use GNU GCC Compiler with default options. 
3. Copy and paste hash.h, stack.h, source.c and testinput files into the CodeBlocks project folder (example: Desktop/ProjectName/) created in previous step.
4. Go back to CodeBlocks. In left side bar under tab "Projects", right-click project name and click "Add Files Recursively" click OK, OK, OK with default options.
5. Under "Build" menu click "Build", then also under "Build" menu click "Run", or just use "Build" and "Run" buttons on toolbar.

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
### Case 5 - Uppercase and lowercase id names, long id names, not all scopes were closed in the end.
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
Output for this test case is very long, please refer to "testoutput5.txt"
