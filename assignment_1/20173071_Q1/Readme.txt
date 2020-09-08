Q1: Problem Statement:
======================
- Design a generic calculator that takes as input an expression and evaluates as outputs the answer.
- Use Self implemented generic stack. No STL allowed.
- The input given will be a correct mathematical statement with matching brackets(if any).
- A single expression can contain both int, double and the answer should be accordingly.
  1. Input: (4+5)/6*3               Output: 4.5
  2. Input: (4+5.6)/3.2+(4+3.888)   Output: 10.888
- Operations to be implemented:
  Addition, Subtraction, Multiplication, Division and Modulo


Solution Outline:
=================
- Create a stack for evaluating operators/operands
- Create a queue for evaluating operators/operands
- Tokenizing the Infix Expression string
- Converting the "infix" expression to "postfix" using stacks & queues.
- Evaluating the postfix expression using a stack.


Source Code Tree:
=================
20173071_Q1
├── Makefile
├── Readme.txt
├── bin
│   ├── Readme.txt
│   └── eval
├── obj
│   ├── ExpEval.o
│   ├── ExpQueue.o
│   ├── ExpStack.o
│   ├── Expression.o
│   └── Readme.txt
└── src
    ├── ExpEval.C
    ├── ExpQueue.C
    ├── ExpQueue.H
    ├── ExpStack.C
    ├── ExpStack.H
    ├── Expression.C
    ├── Expression.H
    └── Node.H

20173071_Q1/obj/*.o   -> are intermediate object files.
20173071_Q1/bin/eval  -> The binary/executable


Compilation Run:
================
20173071_Q1$
20173071_Q1$ make clean;make
Cleaning all the object files and binaries.
rm -f core ./obj/ExpEval.o ./obj/ExpQueue.o ./obj/ExpStack.o ./obj/Expression.o ./bin/eval
g++ -Wall -std=c++1z -c src/ExpEval.C -o obj/ExpEval.o
Compiled src/ExpEval.C successfully.
g++ -Wall -std=c++1z -c src/ExpQueue.C -o obj/ExpQueue.o
Compiled src/ExpQueue.C successfully.
g++ -Wall -std=c++1z -c src/ExpStack.C -o obj/ExpStack.o
Compiled src/ExpStack.C successfully.
g++ -Wall -std=c++1z -c src/Expression.C -o obj/Expression.o
Compiled src/Expression.C successfully.
g++ ./obj/ExpEval.o ./obj/ExpQueue.o ./obj/ExpStack.o ./obj/Expression.o -o bin/eval
Linking Complete.
To start the "Expression Evaluator" run --> ./bin/eval
20173071_Q1$


Sample Execution Runs:
======================
1) Run-1
20173071_Q1$ ./bin/eval
Enter your expression:
(4+5.6)/3.2+(4+3.888)
Infix Expression:
( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 )

Postfix Expression:
4 5.6 + 3.2 / 4 3.888 + +

Result: 10.888


2) Run-2
20173071_Q1$ ./bin/eval
Enter your expression:
(4+5.6)/3.2+(4-30.888)-45
Infix Expression:
( 4 + 5.6 ) / 3.2 + ( 4 - 30.888 ) - 45

Postfix Expression:
4 5.6 + 3.2 / 4 30.888 - + 45 -

Result: -68.888


3) Run-3
20173071_Q1$ ./bin/eval
Enter your expression:
(4+5.6)/3.2+(4-30.888)%45
Infix Expression:
( 4 + 5.6 ) / 3.2 + ( 4 - 30.888 ) % 45

Postfix Expression:
4 5.6 + 3.2 / 4 30.888 - 45 % +

Result: -23.888


4) Run-4
20173071_Q1$ ./bin/eval
Enter your expression:
(3+2)%(0.5*4)
Infix Expression:
( 3 + 2 ) % ( 0.5 * 4 )

Postfix Expression:
3 2 + 0.5 4 * %

Result: 1


5) Run-5
20173071_Q1$ ./bin/eval
Enter your expression:
(4+5.6)/3.2+(4+3.888)+(4+5.6)/3.2+(4+3.888)/(4+5.6)/3.2+(4+3.888)*(4+5.6)/3.2+(4+3.888)-(4+5.6)/3.2+(4+3.888)-(4+5.6)/3.2+(4+3.888)+(4+5.6)/3.2+(4+3.888)+(4+5.6)/3.2+(4+3.888)
Infix Expression:
( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) + ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) / ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) * ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) - ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) - ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) + ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 ) + ( 4 + 5.6 ) / 3.2 + ( 4 + 3.888 )

Postfix Expression:
4 5.6 + 3.2 / 4 3.888 + + 4 5.6 + 3.2 / + 4 3.888 + 4 5.6 + / 3.2 / + 4 3.888 + 4 5.6 + * 3.2 / + 4 3.888 + + 4 5.6 + 3.2 / - 4 3.888 + + 4 5.6 + 3.2 / - 4 3.888 + + 4 5.6 + 3.2 / + 4 3.888 + + 4 5.6 + 3.2 / + 4 3.888 + +

Result: 77.2488
