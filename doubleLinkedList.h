#include <iostream>
#include <string>
#include<cmath>
#include<iomanip>
using namespace std;
struct Node {
	long long num;
	Node* prev;
	Node* next;
	Node(long long n) : num(n), prev(NULL), next(NULL) {}
	Node() :prev(NULL), next(NULL) {}
};

class DoubleLinkedList {

public:
	DoubleLinkedList();   // default construct
	~DoubleLinkedList();  // deconstruct
	DoubleLinkedList(const string& num, int digitsPerNode); // user defined construct
	DoubleLinkedList(const DoubleLinkedList& list);  // copy construct
	DoubleLinkedList& operator = (const DoubleLinkedList& list);  // assignment consturct
	DoubleLinkedList operator + (const DoubleLinkedList& list) const;
	DoubleLinkedList operator * (const DoubleLinkedList& list);//const;
	DoubleLinkedList(int digitspernode);
	void freeMemory();
	void Append(Node *node); //add to the tail 
	void Add(Node *node);//add to the beginning 
	void Print() const;

public:
	Node* head;
	Node* tail;
	int m_digitsPerNode;
};
DoubleLinkedList::DoubleLinkedList() {
	head = NULL;
	tail = NULL;
	m_digitsPerNode = 0;
}
DoubleLinkedList::~DoubleLinkedList() {
	freeMemory();
}
DoubleLinkedList::DoubleLinkedList(int digitspernode) {
	head = NULL;
	tail = NULL;
	m_digitsPerNode = digitspernode;
}
DoubleLinkedList::DoubleLinkedList(const string& numbers, int digitsPerNode) {

	Node *n;  //creating the head
	m_digitsPerNode = digitsPerNode;

	//to know how many nodes you will have
	//if there are remaining digits after all the nodes have been counted 
	//then they will be put in a separate node in the beginning of the list 
	int cl = numbers.length() / digitsPerNode;
	int cl2 = numbers.length() % digitsPerNode;

	string str1; //to store the first node value 

	if (cl2 == 0)
		str1 = numbers.substr(0, digitsPerNode);

	else
		str1 = numbers.substr(0, cl2);

	int g = stoi(str1.c_str()); //converts the value of the string into int 
	n = new Node; //creates a new node
	n->num = g; //stores the value of the string into that node 
	n->next = NULL;
	n->prev = NULL;

	//head and tail point to the same place 
	head = n;
	tail = n;

	if (cl2 == 0) { //if there is no remainder and the length of the number is evenly divided by digitsPerNode 

		for (int i = 1; i < cl; i++) {
			string str2 = numbers.substr(cl2 + i*digitsPerNode, digitsPerNode);
			int d = stoi(str2.c_str()); //convert str2 value to int 

			//create a new Node and assign the value d to it 
			n = new Node;
			n->num = d;
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
		tail->next = NULL;
	}
	else
	{
		for (int i = 0; i < cl; i++) {
			string str2 = numbers.substr(cl2 + i*digitsPerNode, digitsPerNode);
			int d = stoi(str2.c_str());

			n = new Node;
			n->num = d;
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
	}
	tail->next = NULL;
}
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& list) : head(NULL), tail(NULL), m_digitsPerNode(list.m_digitsPerNode)
{
	for (Node* node = list.head; node != NULL; node = node->next) {
		Node* node_temp = new Node(node->num);
		Append(node_temp);
	}
}
DoubleLinkedList DoubleLinkedList::operator+(const DoubleLinkedList& list) const {
	DoubleLinkedList result(m_digitsPerNode);//this is where we will store the result of the sum 
	long long carry = 0;

	//set them equal to the tail because you will start adding from the tail
	Node* node1 = tail;
	Node* node2 = list.tail;

	while (node1 != NULL || node2 != NULL) //while both lists still exist 
	{
		long long num1 = 0; //this is where we will store the values that are in each node 
		long long num2 = 0;

		if (node1 != NULL) //if node1 isnt null then num1 is whatever value is in node 1
		{
			num1 = node1->num;

		}
		if (node2 != NULL) //if node2 isnt null then num2 is whatever value is in node 2 
		{
			num2 = node2->num;
		}

		long long sum = num1 + num2 + carry; //this adds both nodes, the carry is added here so 
											 //it can be updated later in the program and
											 //added once it goes in the while loop again

		long long actual = sum % ((long long)pow(10, m_digitsPerNode)); //calculates what number will go in the node of the result 
		Node *node = new Node(actual);
		result.Add(node); //actual # calculated above a part of the result DLL

		carry = sum / ((long long)pow(10, m_digitsPerNode)); //remainder

															 //move the pointer 
		if (node1 != NULL) {
			node1 = node1->prev;
		}
		if (node2 != NULL) {
			node2 = node2->prev;
		}
	}

	//if there is any leftover after the loop then just put it in a node at the front of the list
	if (carry != 0) {
		Node* node = new Node(carry);
		result.Add(node);
	}

	result.m_digitsPerNode = m_digitsPerNode;

	return result;
}
DoubleLinkedList DoubleLinkedList::operator * (const DoubleLinkedList& list)
{
	DoubleLinkedList result_temp(m_digitsPerNode); //the result while we are calculating 
	DoubleLinkedList result(m_digitsPerNode); //the final result 

	Node *node2 = list.tail; //set the second number to tail 

	int nn = 0;

	while (node2 != NULL) { //outside loop 
		long long carry = 0;

		Node*node1 = tail;

		while (node1 != NULL) //the inside loop 
		{
			long long num1 = node1->num; //set num 1 to the value of wherever the node points to
			long long num2 = node2->num;

			long long num = num1*num2 + carry; //multiply the values and add the carry 
			long long actual = num % ((long long)pow(10, m_digitsPerNode)); //calculate the actual number to be put in the node  
			Node *node = new Node(actual);//make a new node containing the actual value 
			result_temp.Add(node); //add it to the beggining of result temp list 

			carry = (num / (long long)pow(10, m_digitsPerNode));//this calculates the carry/remainder

			node1 = node1->prev; //move the pointer to the previous node 
		}

		//once node 1 is null 
		if (carry != 0) //you need to make another node containing only the carry 
						//this will be the node at the beginning of the list 
		{
			Node *node = new Node(carry);
			result_temp.Add(node); //add it to the result temp list 

		}

		node2 = node2->prev; //move node 2 to the previous node to keep multiplying the bottom number
							 //with the top 

		result = result + result_temp; //add the lists together 

									   //once it finishes with the first result_temp list, for the values of this list to not 
									   //carry out on the other list we will make it a blank list
		result_temp.freeMemory();

		nn++; //you need to keep adding zero nodes as you go along
			  //this is what this for loop does 
		for (int i = 0; i < nn; i++) {
			Node *zero = new Node();

			zero->num = 000; //to the next list we must add a 0 node to be at the end of the list 
							 //so that the lists will add correctly. we do this before adding values to the list 
			result_temp.Add(zero);

		}

	}
	result.m_digitsPerNode = m_digitsPerNode;
	return result;
}
DoubleLinkedList &DoubleLinkedList:: operator= (const DoubleLinkedList & list)
{
	// doublelinkedlist l = l1;
	//l1 = l1
	if (this == &list) {
		return *this;
	}
	head = NULL;
	tail = NULL;
	m_digitsPerNode = list.m_digitsPerNode;

	//free memory
	freeMemory();

	//construct
	for (Node* node = list.head; node != NULL; node = node->next) {
		Node* node_temp = new Node(node->num);
		Append(node_temp);
	}

	return *this;
}
void DoubleLinkedList::Append(Node* node)//add to tail 
{
	if (!tail) {
		head = tail = node;
		return;
	}

	node->prev = tail;
	tail->next = node;
	tail = node;
}
void DoubleLinkedList::freeMemory()
{
	if (!head)
		return;
	else
		while (head) {
			Node *p = head->next;
			delete head;
			head = p;
		}
}
void DoubleLinkedList::Add(Node *node) //add to the beginning of the list 
{
	if (!head) {
		head = tail = node;
		return;
	}
	node->next = head;
	head->prev = node;
	head = node;
}
void DoubleLinkedList::Print() const
{
	Node *temp = head;

	if (temp)
		cout << to_string(temp->num);
		temp = temp->next;
	while (temp != NULL) {
		string str = "";
		string numstr = to_string(temp->num);
		for (int i = 0; i < m_digitsPerNode - numstr.length(); i++)
		str += "0";
		str += numstr;

		cout << str;
		temp = temp->next;
	}
}
