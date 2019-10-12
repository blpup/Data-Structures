// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: A double linked list that can add new nodes, remove nodes, and reverse the linked list order using recursion.
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
using namespace std;


typedef struct NodeSingle {
	float num;
	NodeSingle *next, *prev;
} Node; //A struct node that holds the values - float and 2 pointers to the next and prev node


void reverseList(Node** head);
void printNodes(Node** head);
void deleteNode(Node** head);
void insertNode(Node** head);
void printMenu();
void getNewNode(int num);
void callFunctions(int num, Node** head, int* running);
int getUserNumberChoice();
int getNumBetween(int lowerNum, int greaterNum);
void exitProgram(int *running);

int main(int argc, char **argv) {
	int running = 1; // boolean to check if the program should still be running 
	Node *head = NULL; //pointer to head
	
	while(running) {
		printMenu();
		int userInput = getNumBetween(1,5); // the user input
		callFunctions(userInput, &head, &running);
		cout << endl;
	}
	return 0;
}


// NAME: getNewNode
// INPUT PARAMETERS: num, The number the user inputs; head, the head of the linked list
// OUTPUT: NONE
// Side Effect: Will add a new node to the linked list
// PURPOSE: The function will create a node and attach it to the linked list
//---------------
void getNewNode(int num, Node** head) {
	Node *tempPointer; //a temp pointer
	tempPointer = (Node *) malloc( sizeof(Node) );
	tempPointer -> num = num;
	tempPointer -> next = *head;
	tempPointer -> prev = NULL;
	if( *head != NULL ) {
		(*head) -> prev = tempPointer;
	}
	*head = tempPointer;
	return;
}


// NAME: insertNode
// INPUT PARAMETERS: head, the head of the linked list
// OUTPUT: NONE
// Side Effect: Will take user input and call getNewNode
// PURPOSE: The function will get the user input and create a new node
//---------------
void insertNode(Node** head) {
	cout << "Please enter a number for your new link: ";
	int userInput = getUserNumberChoice();
	getNewNode(userInput, head); //the user input
	return;
}


// NAME: deleteNode
// INPUT PARAMETERS: head, the head of the linked list
// OUTPUT: NONE
// Side Effect: Will delete a node from the linked list
// PURPOSE: The function will delete the last element from the linked list
//---------------
void deleteNode(Node** head) {
	Node *current = *head; //a current pointer to iterate through
	if(*head == NULL) {
		cout << "The list is empty. Please add a node first" << endl;
		return;
	}
	while( (current -> next) != NULL ) {
		current = current -> next;
	}
	if( current -> prev == NULL) {
		*head = NULL;
	} else {
		current -> prev -> next = NULL;
	}
	free(current);
	return;
}


// NAME: printNodes
// INPUT PARAMETERS: head, the head of the linked list
// OUTPUT: NONE
// Side Effect: Will print the nodes in order
// PURPOSE: The function will print the nodes in order
//---------------
void printNodes(Node** head) {
	Node *current = *head; //a current pointer to iterate through
	if( *head == NULL ) {
		cout << "Nothing to print. Please add a node first" << endl;
		return;
	}
	while( current != NULL ) {
		cout << current -> num;
		current = current -> next;
		if( current != NULL ) {
			cout << ", ";
		}
	}
	cout << endl;
	return;
}

// NAME: reverseList
// INPUT PARAMETERS: node, The number the user inputs; head, the head of the linked list
// OUTPUT: NONE
// Side Effect: Will add a new node to the linked list
// PURPOSE: The function will create a node and attach it to the linked list
//---------------
void reverseList(Node** node, Node** head) {
	if(*head == NULL) {
		cout << "Nothing to reverse. Please add a node first" << endl;
		return;
	}
	Node *current = (*node) -> prev; //set the current to prev to reverse the order
	(*node) -> prev = (*node) -> next;
	(*node) -> next = current;
	if((*node) -> prev == NULL) {
		*head = *node;
		return;
	}
	reverseList(&(*node)->prev, head);
	return;
}


// NAME: printMenu
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will print a menu to the console
// PURPOSE: Should print a menu to the console
//---------------
void printMenu() {
	cout << "1.) Insert a node at the beginning." << endl;
	cout << "2.) Delete a node at the end." << endl;
	cout << "3.) Print the nodes." << endl;
	cout << "4.) Reverse the doubly linked list." << endl;
	cout << "5.) Exit the program." << endl;
	cout << "----------" << endl;
	return;
}


// NAME: getNumBetween
// INPUT PARAMETERS: lowerNum, a lower number for a selection; greaterNum, a greater number for a selection
// OUTPUT: NONE
// Side Effect: Will get the user choice for the menu
// PURPOSE: The function will error check and return the choice of the user for the menu
//---------------
int getNumBetween(int lowerNum, int greaterNum) {
	int userInput = 0; //The user input
	int flag = 0; //a flag if true it will continue to run the function
	cout << "Please enter a number between " << lowerNum << "-" << greaterNum <<": ";
	cin >> userInput;
	if( (cin.fail()) ||  (userInput > greaterNum || userInput < lowerNum)) {
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if ( flag ) userInput = getNumBetween(lowerNum, greaterNum);
	return userInput;
}


// NAME: getUserNumberChoice
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will get the user choice for the number for the node
// PURPOSE: The function will error check and return the choice of the user for the number for the node
//---------------
int getUserNumberChoice() {
	int userInput = 0; //The user input
	int flag = 0; //a flag if true it will continue to run the function
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Please enter a number: ";
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if ( flag ) userInput = getUserNumberChoice();
	return userInput;
}


// NAME: exitProgram
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will set the running pointer to 0
// PURPOSE: The function will turn any int pointer to 0. Helps to stop running the program.
//---------------
void exitProgram(int *running){
	*running = 0;
	return;
}

// NAME: callFunctions
// INPUT PARAMETERS: num, the menu choice; head, the head of the linked list; running, a pointer to running to stop the program
// OUTPUT: NONE
// Side Effect: Will call the function the user picked
// PURPOSE: The function will call the function the user picked
//---------------
void callFunctions(int num, Node** head, int* running) {
	switch(num) {
		case 1:
			insertNode(head);
			break;
		case 2:
			deleteNode(head);
			break;
		case 3:
			printNodes(head);
			break;
		case 4:
			reverseList(head, head);
			break;
		case 5:
			exitProgram(running);
			break;
		default:
			cout << "User choice not recognized" << endl;
			break;
	}
	return;
}
