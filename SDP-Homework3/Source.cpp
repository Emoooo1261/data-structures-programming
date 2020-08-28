#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include "BinTree.hpp"

using namespace std;

//Function that counts the number of lines in the text file with the expressions
int numberOfLines(ifstream& is) { //It gets the stream
	string line;
	int numOfLines = 0;
	while (getline(is, line)) { //and after every line the counter adds +1
		++numOfLines;
	}

	is.clear(); //Because eof flag is set
	is.seekg(0, ios::beg); //Return to the beginning of the file

	return numOfLines;
}

//Task a)
BinTree<string>* buildTreeFromPolishNotation(const char* expr) {
	node<string>* root = new node<string>();
	node<string>* curr = root;
	stack<node<string>*> st;

	int len = strlen(expr);
	for (int i = 0; i < len; ++i) {
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*') { //if it's an operator
			curr->data = expr[i]; //save it into the node's data
			st.push(curr); //push the node into the stack
			curr->left = new node<string>(); //create the left node
			curr = curr->left; //and set the iterator to it
		}
		else if ((expr[i] >= '0' && expr[i] <= '9') || (expr[i] >= 'a' && expr[i] <= 'z')) { //else if it's a number or variable
			string num;
			do {
				num += expr[i++];
			}while (expr[i] >= '0' && expr[i] <= '9'); //separate the number from the rest of the string, or if it's a var it just gets saved
			
			curr->data = num; //save it into the node's data
			if (st.empty()) { //if the stack is empty, the string is already traversed too
				break;
			}
			curr = st.top(); //the iterator goes back to the previous operator node
			st.pop(); //then it gets pop off the stack
			curr->right = new node<string>(); //create new right node
			curr = curr->right; //and go to it
		}
	}

	BinTree<string>* tree = new BinTree<string>();
	tree->createWithRoot(root);

	return tree;
}


//Task b) 1)
void traversePostorder(node<string>* curr, string* str) { //Basic Postorder Traversal
	if (curr == NULL) {
		return;
	}
	traversePostorder(curr->left, str);
	traversePostorder(curr->right, str);
	str->append(curr->data + " ");
}
string makeReversePolishNotation(BinTree<string>* tree) {
	node<string>* curr = tree->getRootPtr();
	string* str = new string();
	traversePostorder(curr, str);
	return *str;
}

//Task b) 2)
bool isOperator(string str) {
	return str == "+" || str == "-" || str == "*";
}
void traverseInorder(node<string>* curr, string* str) {
	if (curr == NULL) {
		return;
	}
	//Only needs to check for the left leaf to know that there is also right one, and if one of them is a number then add "("
	if (curr->left && (!isOperator(curr->left->data) || !isOperator(curr->right->data))) {
		str->append("(");
	}
	traverseInorder(curr->left, str);
	str->append(curr->data);
	traverseInorder(curr->right, str);
	if (curr->left && (!isOperator(curr->left->data) || !isOperator(curr->right->data))) {
		str->append(")");
	}
}
string makeInfixNotation(BinTree<string>* tree) {
	node<string>* curr = tree->getRootPtr();
	string* str = new string();
	traverseInorder(curr, str);

	return *str;
}


//Task c)
struct Pair {
	char key;
	int value;
};
int getVariable(vector<Pair>* variables, char a) {
	for (unsigned i = 0; i < variables->size(); ++i) { //Checking if there is already assigned value for this variable
		if (variables->at(i).key == a) {
			return variables->at(i).value;
		}
	}
	cout << "Enter value for '" << a << "'= "; //if there isn't
	Pair pair;
	cin >> pair.value;
	pair.key = a;
	variables->push_back(pair);
	return pair.value;
}
bool isInteger(string str) {
	return str[0] >= '0' && str[0] <= '9';
}
int strToInt(string str, vector<Pair>* variables) { //Function that transforms string to int
	int value = 0;
	if (isInteger(str)) {
		for (unsigned i = 0; i < str.length(); ++i) {
			value = (value * 10) + (str[i] - '0');
		}
	}
	else {
		value = getVariable(variables, str[0]); //if the string isn't an integer then it's a variable
	}
	return value;
}

int calculate(node<string>* curr, vector<Pair>* variables) {
	if (curr == NULL) {
		return 0;
	}
	if (!curr->left && !curr->right) { //if it hits the bottom then its a number
		return strToInt(curr->data, variables); //transforms it into int and returns it
	}
	//if it is operator (there is left and right nodes) 
	int leftValue = calculate(curr->left, variables); //left goes left
	int rightValue = calculate(curr->right, variables); //right goes right

	//then when it hits both bottoms it does the operation
	if (curr->data == "+") {
		return leftValue + rightValue;
	}
	else if (curr->data == "-") {
		return leftValue - rightValue;
	}
	else { //(curr->data == "*")
		return leftValue * rightValue;
	}
}
int calculateExprFromTree(BinTree<string>* tree) {
	node<string>* curr = tree->getRootPtr();
	vector<Pair>* variables = new vector<Pair>();

	return calculate(curr, variables);
}


int main() {
	ifstream inPolishNotationFileStream("PolishNotation.txt"); //open the file
	if (!inPolishNotationFileStream.is_open()) { //check if it's opened sucessfully
		throw runtime_error("Couldn't open file!");
	}
	
	int exprSize = numberOfLines(inPolishNotationFileStream);
	cout << "Number of expressions in the file: " << exprSize << endl;
	cout << endl;
	char** expr = new char*[exprSize];
	string buffer;
	for (int i = 0; i < exprSize; ++i) {
		getline(inPolishNotationFileStream, buffer);
		expr[i] = new char[buffer.length() + 1];
		strcpy(expr[i], buffer.data());
	}
	inPolishNotationFileStream.close(); //close the file


	for (int i = 0; i < exprSize; ++i) {
		cout << "Expression #" << i + 1 << ": " << expr[i] << "\n";

		BinTree<string>* tree = buildTreeFromPolishNotation(expr[i]); //Task a)

		cout << "Reverse Polish Notation: " << makeReversePolishNotation(tree) << endl; //Task b) 1)
		cout << "Infix Notation with parentheses: " << makeInfixNotation(tree) << endl; //Task b) 2)
		cout << "Calculation: " << calculateExprFromTree(tree) << endl; //Task c)
		cout << endl;
	}

	return 0;
}