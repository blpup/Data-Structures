// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Hash tables
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct NodeB {
	int num;
	NodeB *next;
} Node; //A struct node that holds the values num and next.

Node* createNewNode(int num, Node* arrayListItem);
int getModedNumber(int userNum, int memoryLocationSize);
int getUserNumberChoice();
int getUserSelection(int lowerNum, int greaterNum);
void printMenu();
void exitProgram(int *running);
int getMemoryLength();
void printTable(Node* arrayList[], int memoryLength);

int main(int argc, char **argv)
{
	cout << "Welcome to lab 10!\nThis program will demonstrate hashing with chaining using a table of X memory locations\nvia inserting the X, Y, Z, ... integers into the table.\n" << endl;
	int running = 1; //If the program is still running or not.
	int memoryLength = getMemoryLength(); // the length of memory the user wants
	Node *list[memoryLength] = { NULL };
	while( running ) {
		printMenu();
		int userInput = getUserSelection(1,3);//the user input for function calls
		
		if( userInput == 1 ) {
			cout << "Please enter a number for a new integer key:";
			int number = getUserNumberChoice(); // the number the user wants to input
			int arrayLocation = getModedNumber(number, memoryLength); //The index of where the Node should go AKA the mod.
			list[arrayLocation] = createNewNode(number, list[arrayLocation]);
		} else if ( userInput == 2 ) {
			printTable(list, memoryLength);
		} else if ( userInput == 3) {
			exitProgram(&running);
		} else {
			cout << "Wrong input.";
		}
		cout << endl;
	}
	return 0;
}


// NAME: createNewNode
// INPUT PARAMETERS: num, a number to put into the struct; arrayListItem, an array of Nodes
// OUTPUT: NONE
// Side Effect: Will get the user choice for the number for the node
// PURPOSE: The function will error check and return the choice of the user for the number for the node
//---------------
Node* createNewNode(int num, Node* arrayListItem) {
	if(arrayListItem == NULL) {
		arrayListItem = (Node *) malloc( sizeof(Node) );
		arrayListItem -> num = num;
		arrayListItem -> next = NULL;
	}else {
		arrayListItem -> next = createNewNode(num, arrayListItem->next);
	}
	return arrayListItem;
}


// NAME: getModedNumber
// INPUT PARAMETERS: userNum, a number the user inputed ; memoryLocationSize, the array bin size
// OUTPUT: The reminder
// PURPOSE: The function will calculate the mod number
//---------------
int getModedNumber(int userNum, int memoryLocationSize) {
	return userNum % memoryLocationSize;
}


// NAME: printMenu
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will print the menu to the console.
//----------------
void printMenu() {
	cout << "1.) Enter a new integer key." << endl;
	cout << "2.) Print Table." << endl;
	cout << "3.) Exit Program." << endl;
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
	if( cin.fail() || userInput <= 0) {
		cout << "Please enter a number greater than 0: ";
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


// NAME: getUserSelection
// INPUT PARAMETERS: lowerNum, a lower number for a selection; greaterNum, a greater number for a selection
// OUTPUT: NONE
// Side Effect: Will get the user choice for the menu
// PURPOSE: The function will error check and return the choice of the user for the menu
//---------------
int getUserSelection(int lowerNum, int greaterNum) {
	int userInput = 0; //The user input
	int flag = 0; //a flag if true it will continue to run the function
	cout << "Please enter a number between " << lowerNum << "-" << greaterNum <<": ";
	cin >> userInput;
	if( (cin.fail()) ||  (userInput > greaterNum || userInput < lowerNum)) {
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if ( flag ) userInput = getUserSelection(lowerNum, greaterNum);
	return userInput;
}


// NAME: getMemoryLength
// INPUT PARAMETERS: NONE
// OUTPUT: number, the memory length from the user
// PURPOSE: The function will get the memory length from the user then return it.
int getMemoryLength() {
	cout << "Please start by entering a memory location number: ";
	int number = getUserNumberChoice(); //The number the user inputs for the length of memory
	return number;
}


// NAME: printTable
// INPUT PARAMETERS: arrayList, an array of nodes that have lists; memoryLength, the length of the array
// OUTPUT: NONE
// PURPOSE: The function will print the array list and it's node links to the console
//---------------
void printTable(Node* arrayList[], int memoryLength) {
	cout << "-------------------" << endl;
	for(int i = 0; i < memoryLength; i++) {
		Node *current = arrayList[i];
		cout << i << ": ";
		while(current != NULL) {
			cout << current -> num;
			if(current -> next != NULL)
				cout << " -> ";
			current = current -> next;
		}
		cout << endl;
	}
};
