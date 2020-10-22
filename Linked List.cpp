#include<iostream>
using namespace std;

//Structure of Node
struct Node
{
	int data;
	Node* next;
};
class List
{
private:
	Node* head; //Address of Head Node.
	int length; //Get current size of list.
	Node* current_pos;
public:
	List(); //Initialize function
	bool IsFull() const;
	int GetLength() const;
	void MakeEmpty();
	bool RetrieveItem(int& key);
	void InsertAtHead(int value);
	void InsertAtEnd(int value);
	void InsertAt(int index, int value);
	void DeleteFromHead();
	void DeleteFromEnd();
	void DeleteAt(int index);
	void Display();


	void ResetList()
	{
		current_pos = NULL;
	}
	int GetNextItem()
	{
		if (current_pos == NULL)
		{
			current_pos = head;
		}
		else
		{
			current_pos = current_pos->next;
		}
		return current_pos->data;
	}
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
int List::GetLength() const
{
	return length;
}
//Insert a new node with value at the head of List
void List::InsertAtHead(int value)
{
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = head;

	head = newNode;
	length++;
}

//Insert a new node with value at the end of List
void List::InsertAtEnd(int value)
{
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = NULL;

	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		Node* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	length++;
}

//Insert a new node with value at the index of list
//Considering index start from 0;
void List::InsertAt(int index, int value)
{
	if (index == 0)
	{
		this->InsertAtHead(value);
	}
	else if (index == (this->GetLength() - 1))
	{
		this->InsertAtEnd(value);
	}
	else if (index > 0 && index < (this->GetLength() - 1))
	{
		Node* newNode = new Node;
		newNode->data = value;
		Node* temp = head;

		for (int i = 0; i < index-1; i++)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
		length++;
	}
	else
	{
		cout <<"Illigal index specified for insertion";
	}
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

bool List::RetrieveItem(int& a)
{
	bool continued;
	Node * temp;
	temp = head;
	bool found = false;

	continued = (temp != NULL);

	while (continued && !found)
	{
		if (temp->data == a)
			found = true;
		temp = temp->next;
		continued = (temp != NULL);
	}
	return found;
}

//Delete node with value of a from List
void List::DeleteFromHead()
{
	if (head != NULL)
	{
		Node* temp = head;
		head = temp->next;
		delete temp;
		length--;
	}
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
int main()
{
	List A;
	A.Display();
	A.InsertAtEnd(20);
	A.Display();
	A.InsertAtHead(30);
	A.Display();
	A.InsertAtEnd(40);
	A.Display();
	A.InsertAtHead(50);
	//A.InsertAtHead(60);
	A.Display();
	A.InsertAt(0,70);
	A.Display();
	A.InsertAt(1, 90);
	A.Display();
	A.InsertAt(3, 75);
	A.Display();


	return 0;
}