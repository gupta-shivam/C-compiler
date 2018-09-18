# Compiler

Compiler for a C-like language. Converts the code to MIPS Assembly Language which can be run using SPIM.

## It was made in 4 stages
    1: All stages of compiler on a simple C like language using top-down parsing.
    In the rest of stages,bottom up parsing is done using bison. 
    2: Formation of grammar and lexical analysis  
    3: Parsing and generating Parse tree  
    4: Final stage with Semantic analysis and MIPS target code generation

## Steps to run the code :

1. Run the bash file run.sh in terminal : 
        ./run.sh or bash run.sh
    
## Steps to simulate the MIPS code on MARS simulator :

* go to mars simulator folder and run the following command : 
        java Mars.java
* Paste the MIPS code generated from the code to the simulator GUI.
* Assemble the code and run it :) .

## Features of the Language

* Data types : void, int, float, bool, char, string

* Variable Declaration

* Variable Assignment

* Function Declaration

* Logical Expressions involving '&&' and '||'

* Relational operators : '>', '<', '>=', '<=', '==', '<>', '!='

* Arithmatic operators : '+', '-', '*', '/', '%'

* Unary Operators : '+', '-'

* For Loop

* Foreach loop

* While Loop

* Conditional statements

* Nested code blocks

* Explicit Scope specifiers

* breaks in loops

* continues in loops
