//https://www.geeksforgeeks.org/infix-to-prefix-conversion-using-two-stacks/
#include<iostream>
#include<string>
#include<string.h>
using namespace std;

//Structure of Node
struct Node
{
	string data;
	Node* next;
};
class List
{
private:
	Node* head; //Address of Head Node.
	int length; //Get current size of list.
public:
	List(); //Initialize function
	bool IsFull() const;
	bool IsEmpty() const;
	int GetLength() const;
	void MakeEmpty();
	string ReadHead() const;
	void InsertAtHead(string value);
	string DeleteFromHead();
	void Display();
};

List::List() // Constructor of class
{
	length = 0;
	head = NULL;
}

//Check if there is enough system memory available;
bool List::IsFull() const
{
	Node* temp;
	try {
		temp = new Node;
		delete temp;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

bool List::IsEmpty() const
{
	return (length == 0 || head == NULL);
}

void List::MakeEmpty()
{
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	length = 0;
}

int List::GetLength() const
{
	return length;
}

//Function returns the data vaule at head of the list, use as helper function to implement top() of stack
string List::ReadHead() const
{
	string data = "";
	if (head != NULL)
	{
		data = head->data;
	}
	return data;
}

//Insert a new node with value at the head of List
void List::InsertAtHead(string value)
{
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = head;

	head = newNode;
	length++;
}
//Delete node with value of a from List
string List::DeleteFromHead()
{
	string data = "";
	if (head != NULL)
	{
		Node* temp = head;
		head = temp->next;
		data = temp->data;
		delete temp;
		length--;
	}
	return data;
}

//Show the complete list to user
void List::Display()
{
	if (head != NULL)
	{
		Node * temp = head;
		while (temp != NULL)
		{
			cout << "| " << temp->data << " |";
			if (temp->next != NULL)
			{
				cout << " -> ";
			}
			temp = temp->next;
		}
		cout << endl;
	}
	else
	{
		cout << "List is Empty\r\n";
	}
}


class Stack
{
private:
	List list;
public:
	bool isFull() const;
	bool isEmpty() const;
	string top() const;
	void push(string value);
	string pop();
};

bool Stack::isFull() const
{
	return list.IsFull();
}
bool Stack::isEmpty() const
{
	return list.IsEmpty();
}
string Stack::top() const
{
	return list.ReadHead();
}
void Stack::push(string value)
{
	list.InsertAtHead(value);
}
string Stack::pop()
{
	return list.DeleteFromHead();
}

enum expressionType { prefix, infix, postfix };

class Expression
{
private:
	string expression;
	expressionType expression_type;

	int evaluatePrefix() const;
	int evaluateInfix() const;
	int evaluatePostfix() const;

	void prefixToInfix();
	void prefixToPostfix();
	void infixToPrefix();
	void infixToPostfix();
	void postfixToPrefix();
	void postfixToInfix();

	bool  isOperand(string ch) const
	{
		// If the scanned character is an operand, add it to output string. 
		return ((ch >= "a" && ch <= "z") || (ch >= "A" && ch <= "Z"));
	}

	bool  isOperator(string ch) const
	{
		// If the scanned character is an operand, add it to output string. 
		return (ch == "^" || ch == "*" || ch == "/" || ch == "+" || ch == "-");
	}
	// to check the precedence of operators.
	int precedence(string c)
	{
		if (c == "^")
			return 3;
		else if (c == "*" || c == "/")
			return 2;
		else if (c == "+" || c == "-")
			return 1;
		else
			return -1;
	}


public:
	Expression()
	{
		this->expression = "00000000000000000000000";
		this->expression_type = infix;
	}

	void convertExpression(expressionType convertTo)
	{
		if (this->expression_type == prefix)
		{
			switch (convertTo)
			{
			case infix:
				//prefixToInfix();
				break;
			case postfix:
				//prefixToPostfix();
				break;
			}
		}
		else if (this->expression_type == infix)
		{
			switch (convertTo)
			{
			case prefix:
				infixToPrefix();
				break;
			case postfix:
				infixToPostfix();
				break;
			}
		}
		else if (this->expression_type == postfix)
		{
			switch (convertTo)
			{
			case prefix:
				//postfixToPrefix();
				break;
			case infix:
				//postfixToInfix();
				break;
			}
		}
	}
	int evaluateExpression()
	{
		switch (this->expression_type)
		{
		case prefix:
			evaluatePrefix();
			break;
		case infix:
			evaluateInfix();
			break;
		case postfix:
			evaluatePostfix();
			break;
		}
	}
	void Display()
	{
		switch (this->expression_type)
		{
		case prefix:
			cout << "Prefix ";
			break;
		case infix:
			cout << "Infix ";
			break;
		case postfix:
			cout << "Postfix ";
			break;
		}
		cout << "Notation: " << this->expression << endl;
	}
	void setExpression(string expression)
	{
		this->expression = expression;
	}
};

void Expression::infixToPostfix()
{
	Stack stack;
	string postfixStr;
	//Check weather it is an infix expression or not.
	if (this->expression_type == infix)
	{
		for (int i = 0; i < this->expression.length(); i++)
		{
			// If the scanned character is an operand, add it to output string. 
			string ch(1, this->expression[i]);
			if (isOperand(ch))
			{
				postfixStr += ch;
			}
			// If the scanned character is an ‘(‘, push it to the stack. 
			else if (ch == "(")
			{
				stack.push(ch);
			}

			// If the scanned character is an ‘)’, pop and to output string from the stack 
			// until an ‘(‘ is encountered. 
			else if (ch == ")")
			{
				while (stack.top() != "(" && !stack.isEmpty())
				{
					string op = stack.pop();
					postfixStr += op;
				}
				if (stack.top() == "(")
				{
					stack.pop();
				}
			}
			//If an operator is scanned 
			else {
				while (!stack.isEmpty() && precedence(ch) <= precedence(stack.top()))
				{
					string op = stack.pop();
					postfixStr += op;
				}
				stack.push(ch);
			}
		}
		//Pop all the remaining elements from the stack 
		while (!stack.isEmpty())
		{
			string op = stack.pop();
			postfixStr += op;
		}

		this->expression = postfixStr;
		this->expression_type = postfix;
	}
	else
	{
		cout << "Sorry given expression is not in Infix notation." << endl;
	}
}

//This funcion will convert expression in infix notation to prefix notation
void Expression::infixToPrefix()
{
	Stack operators_stack;
	Stack operands_stack;
	string prefixStr;
	//Check weather it is an infix expression or not.
	if (this->expression_type == infix)
	{
		for (int i = 0; i < this->expression.length(); i++)
		{
			// If the scanned character is an operand, add it to output string. 
			string ch(1,this->expression[i]);

			// If current character is an 
			// opening bracket, then 
			// push into the operators stack. 
			if (ch == "(")
			{
				operators_stack.push(ch);
			}

			// If current character is a 
			// closing bracket, then pop from 
			// both stacks and push result 
			// in operands stack until 
			// matching opening bracket is 
			// not found. 
			else if (ch == ")")
			{
				while (!operators_stack.isEmpty() && operators_stack.top() != "(") 
				{
					// operand 1 
					string op1 = operands_stack.pop();

					// operand 2 
					string op2 = operands_stack.pop();

					// operator 
					string op = operators_stack.pop();

					// Add operands and operator 
					// in form operator + 
					// operand1 + operand2. 

					string tmp = op + op2 + op1;
					operands_stack.push(tmp);
				}

				// Pop opening bracket from 
				// stack. 
				operators_stack.pop();
			}
			// If current character is an 
			// operand then push it into 
			// operands stack. 
			else if (!isOperator(ch)) {
				operands_stack.push(ch);
			}

			// If current character is an 
			// operator, then push it into 
			// operators stack after popping 
			// high priority operators from 
			// operators stack and pushing 
			// result in operands stack. 
			else {
				while (!operators_stack.isEmpty() && precedence(ch) <=	precedence(operators_stack.top())) {

					string op1 = operands_stack.pop();
					string op2 = operands_stack.pop();
					string op = operators_stack.pop();

					string tmp = op + op2 + op1;
					operands_stack.push(tmp);
				}

				operators_stack.push(ch);
			}
		}

		// Pop operators from operators stack 
		// until it is empty and add result 
		// of each pop operation in 
		// operands stack. 
		while (!operators_stack.isEmpty()) {
			string op1 = operands_stack.pop();
			string op2 = operands_stack.pop();
			string op = operators_stack.pop();
			string tmp = op + op2 + op1;
			operands_stack.push(tmp);
		}

		// Final prefix expression is 
		// present in operands stack. 
		this->expression = operands_stack.top();
		this->expression_type = prefix;
	}
	else
	{
		cout << "Sorry given expression is not in Infix notation." << endl;
	}
}
int main()
{
	Expression E1, E2;

	string expression = "a+b*(c^d-e)^(f+g*h)-i"; //sample infix string to convert into a postfix string
	string expression2 = "(A-B/C)*(A/K-L)";  // sample infix string to convert into a prefix string
	
	//Experiment of postfix string
	E1.setExpression(expression);
	E1.Display();
	E1.convertExpression(postfix);
	E1.Display();

	//Experient of prefix string
	E2.setExpression(expression2);
	E2.Display();
	E2.convertExpression(prefix);
	E2.Display();


	return 0;
}
