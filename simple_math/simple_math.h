typedef enum
{
	NONE = 0u, ADD, SUB, MUL, DIV
} MATH_OP;


#ifndef SIMPLE_MATH_H
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);
int factorial(int value);

#endif
