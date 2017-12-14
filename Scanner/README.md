# Project 1 - Phase 1 - Lexical analysis
## Team Members
Robert M.
Jon Q.
Hongjie Z.

## Environment
```
Lex: flex 2.5.35, 2.6.0, 2.6.1
Language: C
OS: Ubuntu 16.10, CentOS 6.8
IDE/Editor: Notepad++ v7, VIM 7.4.1829
Compiler: gcc 4.4.7, 5.4.0, 6.2.0
```

## Components and Functions
### hash.h - The symbol table modified from Project 0
### stack.h - The active scope number stack from Project 0
### FP.l - The lex definition file for FP language

## Constraint
This program is fully tested in Ubuntu. We assume this program will work in Linux-like systems, but not in Windows-like systems.

## Compile and Run in Linux
Put hash.h, stack.h, FP.l and sample.fp files in the same directory 
Launch a Terminal, navigate to the directory that contains the files described above, execute following command
```
flex FP.l
gcc lex.yy.c
```
Execute the program with an input sample file
```
./a.out < sample.fp
```

## Test
### Input
See sample.fp
### Output Interpretation
1. Identifier is a string that starts with a lowercase or uppercase letter and followed by 0 to 5 lowercase or uppercase letters or numbers. Since “myStrng” in the input has the length of 7, it is not a valid identifier. And the program output “myStrng” as Unrecognized.
2. Integer is a single digit 0 or any positive number or any negative number which has a “-” before the negative number and have zero or more blank(s) in between. “+999” is not a valid Integer. However it will be interpreted as a Special Symbol “+” which is an operator and a positive Integer 999.
3. Float has a decimal point and have at least one digit on each side. It also has a “-” if it’s negative. And if it’s 0.0, there can only be one 0 on the left side of the decimal point. 00.0 is not a valid Float.
4. Char-String is character string which is enclosed within () and can be any length of lowercase or uppercase letters, numbers, spaces and literal \ which represent a new line.
5. Boolean can only be “T” or “F”, and these two letters will not be recognized as Identifier. 
6. White Space is spaces, tabs or return characters, which will be skipped. So there’s no output.
7. Keyword is the set given in the project instruction and will not be recognized as Identifier.
8. Special Symbol is the set given in the project instruction. This program doesn’t aim to distinguish its application. However, “{“ and “}” is used for open and close scopes for the Symbol Table, so they will not be stored into the Symbol Table. And “(“ and “)” will be recognized as Special Symbol only if it’s not captured by the Char-String.
9. Unrecognized is all the other things that were not captured by above rules.
### Output
```
Special Symbol: {
Keyword: Program
Identifier: Sample
Special Symbol: {
Keyword: Function
Identifier: facto
Identifier: VAL
Special Symbol: {
Keyword: if
Special Symbol: {
Special Symbol: <
Identifier: VAL
Integer: 0
Special Symbol: }
Keyword: then
Special Symbol: {
Special Symbol: =
Identifier: retVal
Integer: -1
Special Symbol: }
Keyword: else
Special Symbol: {
Special Symbol: =
Identifier: retVal
Integer: 1
Special Symbol: }
Special Symbol: {
Keyword: while
Special Symbol: {
Special Symbol: >
Identifier: VAL
Integer: 0
Special Symbol: }
Keyword: do
Special Symbol: {
Special Symbol: =
Identifier: retVal
Special Symbol: {
Special Symbol: *
Identifier: retVal
Identifier: VAL
Special Symbol: }
Special Symbol: }
Special Symbol: {
Special Symbol: =
Identifier: VAL
Special Symbol: {
Special Symbol: -
Identifier: VAL
Integer: 1
Special Symbol: }
Special Symbol: }
Special Symbol: }
Special Symbol: }
Keyword: return
Identifier: retVal
Special Symbol: {
Keyword: Function
Identifier: rtrn
Identifier: a
Identifier: b
Special Symbol: {
Keyword: if
Special Symbol: {
Special Symbol: <
Identifier: a
Identifier: b
Special Symbol: }
Keyword: then
Special Symbol: {
Special Symbol: =
Identifier: ret
Float: -0.001000
Special Symbol: }
Special Symbol: }
Keyword: if
Special Symbol: {
Special Symbol: >
Identifier: a
Identifier: b
Special Symbol: }
Keyword: then
Special Symbol: {
Special Symbol: =
Identifier: ret
Float: 0.001000
Special Symbol: }
Keyword: else
Special Symbol: {
Special Symbol: =
Identifier: ret
Integer: 0
Special Symbol: }
Special Symbol: }
Special Symbol: }
Keyword: return
Identifier: ret
Special Symbol: {
Keyword: Function
Identifier: getEle
Identifier: index
Identifier: lst
Special Symbol: {
Keyword: if
Special Symbol: {
Special Symbol: !=
Identifier: index
Identifier: lst
Special Symbol: }
Keyword: then
Special Symbol: {
Char-String: (pound f)
Special Symbol: }
Special Symbol: }
Special Symbol: {
Keyword: if
Special Symbol: {
Special Symbol: =
Identifier: index
Integer: 1
Special Symbol: }
Special Symbol: {
Special Symbol: =
Identifier: lst
Identifier: lst
Integer: -1
Special Symbol: }
Special Symbol: {
Identifier: getEle
Special Symbol: {
Special Symbol: -
Identifier: index
Integer: 1
Special Symbol: }
Special Symbol: {
Identifier: lst
Special Symbol: }
Special Symbol: }
Special Symbol: }
Special Symbol: }
Keyword: return
Identifier: lst
Special Symbol: {
Special Symbol: =
Unrecognized: myStrng
Char-String: (I like lex and yacc)
Special Symbol: }
Special Symbol: {
Keyword: print
Special Symbol: {
Identifier: facto
Integer: 999
Special Symbol: }
Special Symbol: }
Special Symbol: {
Keyword: print
Special Symbol: {
Identifier: rtrn
Integer: 7
Integer: 5
Special Symbol: }
Special Symbol: }
Special Symbol: {
Keyword: print
Special Symbol: {
Identifier: getEle
Integer: 2
Special Symbol: {
Special Symbol: =
Identifier: list
Char-String: (abcd)
Special Symbol: }
Special Symbol: }
Special Symbol: }
Special Symbol: }

========= Finished reading the input file =========

Data at index 0 in Symbol Table:
Scope	Type                 String
---------------------------------------
36      String               (abcd)
29      String               (I like lex and yacc)
22      String               (pound f)

Data at index 1 in Symbol Table:
Scope	Type                 String
---------------------------------------
35      Integer               2
0       Keyword              return
1       Keyword              return
9       Special Symbol       *

Data at index 4 in Symbol Table:
Scope	Type                 String
---------------------------------------
27      Special Symbol       -
21      Special Symbol       !=
11      Special Symbol       -

Data at index 7 in Symbol Table:
Scope	Type                 String
---------------------------------------
35      Identifier           getEle
19      Identifier           getEle
18      Integer              0
7       Integer              0
3       Integer              0

Data at index 8 in Symbol Table:
Scope	Type                 String
---------------------------------------
0       Identifier           ret
18      Identifier           ret
17      Identifier           ret
15      Identifier           ret

Data at index 9 in Symbol Table:
Scope	Type                 String
---------------------------------------
23      Keyword              if
20      Keyword              if
12      Keyword              if
13      Keyword              if
2       Keyword              if

Data at index 10 in Symbol Table:
Scope	Type                 String
---------------------------------------
27      Integer               1
24      Integer               1
11      Integer               1
5       Integer               1

Data at index 11 in Symbol Table:
Scope	Type                 String
---------------------------------------
6       Keyword              while

Data at index 12 in Symbol Table:
Scope	Type                 String
---------------------------------------
19      Identifier           index

Data at index 14 in Symbol Table:
Scope	Type                 String
---------------------------------------
19      Keyword              Function
1       Keyword              Function

Data at index 15 in Symbol Table:
Scope	Type                 String
---------------------------------------
33      Integer               5
12      Identifier           a

Data at index 16 in Symbol Table:
Scope	Type                 String
---------------------------------------
12      Identifier           b
1       Identifier           retVal
8       Identifier           retVal
5       Identifier           retVal
4       Identifier           retVal

Data at index 19 in Symbol Table:
Scope	Type                 String
---------------------------------------
14      Special Symbol       <
3       Special Symbol       <
0       Keyword              Program

Data at index 20 in Symbol Table:
Scope	Type                 String
---------------------------------------
36      Special Symbol       =
29      Special Symbol       =
25      Special Symbol       =
24      Special Symbol       =
18      Special Symbol       =
17      Special Symbol       =
15      Special Symbol       =
10      Special Symbol       =
8       Special Symbol       =
5       Special Symbol       =
4       Special Symbol       =

Data at index 21 in Symbol Table:
Scope	Type                 String
---------------------------------------
0       Identifier           lst
19      Identifier           lst
16      Special Symbol       >
7       Special Symbol       >

Data at index 22 in Symbol Table:
Scope   Type                 String
---------------------------------------
15      Float                -0.001

Data at index 24 in Symbol Table:
Scope	Type                 String
---------------------------------------
12      Keyword              else
2       Keyword              else

Data at index 26 in Symbol Table:
Scope	Type                 String
---------------------------------------
17      Float                0.001

Data at index 28 in Symbol Table:
Scope	Type                 String
---------------------------------------
0       Identifier           Sample

Data at index 30 in Symbol Table:
Scope	Type                 String
---------------------------------------
6       Keyword              do

Data at index 31 in Symbol Table:
Scope	Type                 String
---------------------------------------
20      Keyword              then
12      Keyword              then
13      Keyword              then
2       Keyword              then

Data at index 32 in Symbol Table:
Scope	Type                 String
---------------------------------------
36      Identifier           list
33      Identifier           rtrn
31      Identifier           facto
25      Integer              -1
12      Identifier           rtrn
4       Integer              -1
1       Identifier           facto

Data at index 34 in Symbol Table:
Scope	Type                 String
---------------------------------------
34      Keyword              print
32      Keyword              print
30      Keyword              print

Data at index 36 in Symbol Table:
Scope	Type                 String
---------------------------------------
31      Integer               999

Data at index 38 in Symbol Table:
Scope	Type                 String
---------------------------------------
33      Integer               7

Data at index 39 in Symbol Table:
Scope	Type                 String
---------------------------------------
1       Identifier           VAL

Active Block Contents nothing
```
