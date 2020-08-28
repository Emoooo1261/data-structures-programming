#define _CRT_SECURE_NO_WARNINGS //strcpy gives error in Visual studio
#include "Expressions.h"

Expressions::Expressions(const char* fileName) {
	setExpr(fileName); //calls the method to set the size and the expressions

	cout << size << endl; //print the size
	int temp;
	for (unsigned i = 0; i < size; ++i) { //print all the expressions and their result or if they are invalid prints "invalid"
		temp = solveExpression(expr[i]);
		if (temp < 0) {
			cout << expr[i] << " | Invalid!" << endl;
		}
		else {
			cout << expr[i] << " | RESULT = " << temp << endl;
		}
	}
}

Expressions::~Expressions() {
	for (unsigned i = 0; i < size; ++i) {
		delete expr[i];
	}
	delete[] expr;
}

int Expressions::solveExpression(const char* expr) {
	stack<char> operations; //will be storing the operations from the expression, operations will be: 'f', 'm', 'g', '(' and ','
	stack<int> values; //will be storing the numeric values
	int res = 0;
	int len = strlen(expr);

	for (int i = 0; i < len; ++i) {
		if (expr[i] >= '0' && expr[i] <= '9') { //if the element is a digit, it will look if there are more digits and make them into a number,
												//then push them in the values stack
			int value = 0;
			do {
				value = (value * 10) + (expr[i] - '0');
				++i;
			} while (expr[i] >= '0' && expr[i] <= '9');
			values.push(value);
			--i;
		}
		else if (expr[i] == ')') { //if the element is a closing bracket then it should make the last stored operation
			if (operations.empty()) { //if there are no operation then the expression is invalid
				return -1;
			}
			char op;
			op = operations.top();
			operations.pop();

			if ((op != '(' && op != ',') || operations.empty() || values.empty()) { //if the operation isn't ( or , then its invalid
				return -1;
			}
			else {
				if (op == '(') { //if its ( then it gets ignored
					op = operations.top();
					operations.pop();
				}
				else if (op == ',') { //if its , it gets the next element from the stack, that should be (
					op = operations.top();
					operations.pop();
					if (operations.empty() || op != '(') {
						return -1;
					}
					else { //if it is, it gets ignored and then there should be only the letters
						op = operations.top();
						operations.pop();
					}
				}
			}
			if (op == 'f') { //looking for valid operation and then doing it and pushing the result in the values stack
				int val = values.top();
				values.pop();
				values.push(exprF(val));
			}
			else if (op == 'g') {
				int val = values.top();
				values.pop();
				values.push(exprG(val));
			}
			else if (op == 'm') {
				int val1 = values.top();
				values.pop();
				if (values.empty()) {
					return -1;
				}
				int val2 = values.top();
				values.pop();
				values.push(exprM(val1, val2));
			}
			else { //if its different letter its invalid
				return -1;
			}
		}
		else { //it pushes everything except for ' ' and numbers, so f(    15 ) is a valid expression
			if (expr[i] != ' ') {
				operations.push(expr[i]);
			}
		}
	}
	if (values.empty() || !operations.empty()) { //if the values stack is empty and the operations isn't then the expression is invalid
		return -1;
	}
	res = values.top(); //it gets the should be last value that is the result
	values.pop();
	if (values.empty()) //and if its the last returns it
	{
		return res;
	}
	else {
		return -1;
	}
}
int Expressions::factorial(int num) {
	if (num > 1)
		return num * factorial(num - 1);
	else
		return 1;
}
void Expressions::setExpr(const char* fileName) {
	std::ifstream inExpressionsFileStream(fileName); //open the file
	if (!inExpressionsFileStream.is_open()) { //check if it's opened sucessfully
		throw std::runtime_error("Couldn't open file!");
	}

	inExpressionsFileStream >> size; //read the first line (should be num that is the size)
	if (size == 0) {
		throw std::runtime_error("Invalid size!");
	}
	expr = new char*[size];
	inExpressionsFileStream.ignore();

	char buffer[1024];
	for (unsigned i = 0; i < size; ++i) { //save the next 'size' number of lines in the expr**
		inExpressionsFileStream.getline(buffer, 1024);
		expr[i] = new char[strlen(buffer) + 1];
		strcpy(expr[i], buffer);
	}
	inExpressionsFileStream.close(); //close the file even tho it gets closed automatically because the end of the method..
}
int Expressions::exprF(int num) {
	return (num * num) % 100;
}
int Expressions::exprG(int num) {
	return factorial(num % 5);
}
int Expressions::exprM(int num1, int num2) {
	return num1 <= num2 ? num1 : num2;
}