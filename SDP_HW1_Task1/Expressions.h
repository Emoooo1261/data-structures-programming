#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class Expressions
{
	char** expr; //array of char arrays to store the expressions
	unsigned size; //number of expressions
public:
	Expressions(const char* fileName); //the constructor needs a file name with the expressions
	~Expressions();

	void setExpr(const char* fileName); //reads the file and sets the size and the expressions
	int solveExpression(const char* expr); //solves the given expression or returns -1 if its invalid
	int factorial(int num);
	int exprF(int num);
	int exprG(int num);
	int exprM(int num1, int num2);
	
};

#endif // !EXPRESSIONS_H
