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


Solution:
=========
- Create a stack for evaluating expressions. For this problem a character stack is enough to store operators.
- Trim away all the white spaces from the expression if any.
- Converting the "infix" expression to "prefix".
- Evaluating the prefix expression using a stack.
