//20009320 Lukas Jehle

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string.h>

using namespace std;

/* implement your stack here */
struct Node {
	int data;
	Node* next;
};


class Stack {
private:
	Node* listpointer;
public:
	Stack();
	~Stack();
	void Push(int newthing);
	void Pop();
	int Top();
	bool isEmpty();
};

Stack::Stack() {
	//constructor. kind of like initialisation or "creating" the first element of LL
	listpointer = NULL;
}
Stack::~Stack() {
	//destructor. just here to keep compiler happy.
}
void Stack::Push(int newthing) {
	//place newthing on the top of the stack
	Node* temp = new Node; //create new temporary variable to store a new node
	temp->data = newthing;
	temp->next = listpointer;
	listpointer = temp;
}
void Stack::Pop() {
	//remove top item of stack implemented as LL
	Node* p;
	p = listpointer;
	if (listpointer != NULL) { //ensures stack is not empty
		listpointer = listpointer->next;
		delete p; //this in effect deletes where listpointer was pointing to. i.e frees up the previous stack item
	}
}
int Stack::Top() { //only use in conjuction with isempty to avoid seg fault.
	return listpointer->data;
}
bool Stack::isEmpty() {
	if (listpointer == NULL) {
		return true;
	}
	return false;
}



int main(int argc, char** argv) {//get arguments from command line, i.e., yourexec filename
	Stack S;
	int result, op1, op2, number, count = 0;
	char oper;
	string expression;
	ifstream input_file;
	if (argc != 2) {
		cout << "needs a filename as argument  " << endl;
		exit(0);
	}
	input_file.open(argv[1]);
	if (!input_file.good()) {
		cout << "cannot read file " << argv[1] << endl;
		exit(0);
	}
	while (!input_file.eof()) {
		getline(input_file, expression);
		if (isdigit(expression[0])) {
			stringstream line(expression);
			line >> number;
			cout << "reading number " << number << endl;
			//modify here to deal with the Stack
			//PUSH number
			S.Push(number);
			count++;
		}
		else {
			if (expression[0] == '+' || expression[0] == '-' || expression[0] == '/' || expression[0] == '*') {
				stringstream line(expression);
				line >> oper;
				cout << "reading operator " << oper << endl;
				//op2 = TOP
				//POP
				//op1 = TOP 
				//POP
				//compute result
				//PUSH result
				if (S.isEmpty() == false) {
					op2 = S.Top();
					S.Pop();
					count--;
				}
				if (S.isEmpty() == false) {
					op1 = S.Top();
					S.Pop();
					count--;
				}
				else {
					cout << "too many operators" << endl;
					break;
				}
				int result;
				if (oper == '+') result = op2 + op1;
				if (oper == '*') result = op2 * op1;
				if (oper == '/') result = op1 / op2;
				if (oper == '-') result = op1 - op2;
				S.Push(result);
				count++;

			}
		}
	}
	//finalanswer = TOP
	//the last element of the stack should be the final answer...
	if (count > 1) {
		cout << "too many numbers" << endl;
	}
	else if (S.isEmpty() == false) {
		cout << "The result is " << S.Top() << endl;
	}
}
