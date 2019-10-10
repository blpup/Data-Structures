#include <stdio.h>
#include <iostream>
using namespace std;


typedef struct NodeSingle {
	float num;
	NodeSingle *next, *prev;
} Node; //A struct node that holds the values - float and a pointer to the next node.


int reverseList();
int printNodes();
int deleteNode();
int insertNode(Node** head);
int getMenuChoice();
void printMenu();
void getNewNode(int num);
void callFunctions(int num, Node** head);

int main(int argc, char **argv) {
	int userInput = 0;
	Node *head = NULL;
	
	printMenu();
	userInput = getMenuChoice();
	
	callFunctions(userInput, &head);
	
	cout << head -> num;
	return 0;
}

void getNewNode(int num, Node** head) {
	Node *tempPointer;
	tempPointer = (Node *) malloc( sizeof(Node) );
	tempPointer -> num = num;
	tempPointer -> next = *head;
	tempPointer -> prev = NULL;
	if( *head != NULL ) {
		*head.prev = tempPointer;
	}
	*head = tempPointer;
}
int insertNode(Node** head) {
	int userInput = 0;
	cout << "Please enter a number for your new link: ";
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Either please enter a smaller number or enter a number." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return 0;
	}
	return 1;
}

int deleteNode() {
	
	return 0;
}

int printNodes() {
	
	return 0;
}

int reverseList() {
	
	return 0;
}

void printMenu() {
	cout << "1.) Insert a node at the beginning." << endl;
	cout << "2.) Delete a node at the end." << endl;
	cout << "3.) Print the nodes." << endl;
	cout << "4.) Reverse the doubly linked list." << endl;
}

int getMenuChoice() {
	int userInput = 0; //The user input
	int flag = 0;
	cout << "Please enter a number between 1-4: ";
	cin >> userInput;
	if( (cin.fail()) ||  (userInput > 4 || userInput < 1)) {
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if ( flag ) userInput = getMenuChoice();
	return userInput;
}
void callFunctions(int num, Node* head) {
	switch(num) {
		case 1:
			insertNode(&head);
			break;
		case 2:
			deleteNode();
			break;
		case 3:
			printNodes();
			break;
		case 4:
			reverseList();
			break;
		default:
			cout << "User choice not recognized" << endl;
			break;
	}
}
