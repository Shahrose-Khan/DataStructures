#include<iostream>
#include<string>
#include<string.h>
using namespace std;

//Structure of Node
struct Node
{
	char data;
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
	char ReadHead() const;
	void InsertAtHead(char value);
	char DeleteFromHead();
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
char List::ReadHead() const
{
	char data = '`';
	if (head != NULL)
	{
		data = head->data;
	}
	return data;
}

//Insert a new node with value at the head of List
void List::InsertAtHead(char value)
{
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = head;

	head = newNode;
	length++;
}
//Delete node with value of a from List
char List::DeleteFromHead()
{
	char data = '`';
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
		char top() const;
		void push(char value);
		char pop();
};

bool Stack::isFull() const
{
	return list.IsFull();
}
bool Stack::isEmpty() const
{
	return list.IsEmpty();
}
char Stack::top() const
{
	return list.ReadHead();
}
void Stack::push(char value)
{
	list.InsertAtHead(value);
}
char Stack::pop()
{
	return list.DeleteFromHead();
}

enum expressionType{postfix, infix, prefix};

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

	bool  isOperand (char ch) const
	{
		// If the scanned character is an operand, add it to output string. 
		return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
	}

	// to check the precedence of operators.
	int precedence(char c)
	{
		if (c == '^')
			return 3;
		else if (c == '*' || c == '/')
			return 2;
		else if (c == '+' || c == '-')
			return 1;
		else
			return -1;
	}


public:
	Expression()
	{
		/*int i;
		for (i = 0; i < 30-1; i++)
		{
			expression[i] = '0';
		}*/
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
				//infixToPrefix();
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
			char ch = this->expression[i];
			if (isOperand(ch))
			{
				postfixStr += ch;
			}
			// If the scanned character is an ‘(‘, push it to the stack. 
			else if (ch == '(')
			{
				stack.push(ch);
			}

			// If the scanned character is an ‘)’, pop and to output string from the stack 
			// until an ‘(‘ is encountered. 
			else if (ch == ')')
			{
				while (stack.top() != '(' && !stack.isEmpty())
				{
					char op = stack.pop();
					postfixStr += op;
				}
				if (stack.top() == '(')
				{
					stack.pop();
				}
			}
			//If an operator is scanned 
			else {
				while (!stack.isEmpty() && precedence(ch) <= precedence(stack.top()))
				{
					char op = stack.pop();
					postfixStr += op;
				}
				stack.push(ch);
			}
		}
		//Pop all the remaining elements from the stack 
		while (!stack.isEmpty())
		{
			char op = stack.pop();
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
int main()
{
	Expression E1;
	string expression = "a+b*(c^d-e)^(f+g*h)-i";
	E1.setExpression(expression);
	E1.Display();
	E1.convertExpression(postfix);
	E1.Display();
	return 0;
}
