#include "simple_math.h"

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

int factorial(int value)
{
	int result = 1;
	for (int i = 1; i < value; i++)
	{
		result *= i;
	}
	return result;
}
