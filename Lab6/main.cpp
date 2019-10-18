
// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: A tree structure that will insert, delete, and locate an Item in a Tree.
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------


#include <stdio.h>
#include <iostream>

using namespace std;


typedef struct NodeB {
	int num;
	NodeB *right,*left;
} Node; //A struct node that holds the values - float and a pointer to the next node.


Node *deleteItem(int number, Node *Tree);
Node *insertItem(int number, Node *Tree);
Node *locateItem(int number, Node *Tree);
Node *callFunctions(int userInput, Node *Tree);
int getUserSelection(int lowerNum, int greaterNum);
void printMenu();

int main(int argc, char **argv)
{
	Node *Tree = NULL;
	int userInput = 0; //the user input for function calls
	int running = 1; //If the program is still running or not
	while( running ) {
		userInput = 0;
		printMenu();
		userInput = getUserSelection(1,3);
		Tree = callFunctions(userInput, Tree);
		cout << endl;
	}
	return 0;
}


// NAME: locateItem
// INPUT PARAMETERS: number, The number the user wants to insert; Tree, the whole Tree
// OUTPUT: It will return the Tree
// PURPOSE: The function will take a user input and locate it inside the tree
//----------------
Node *locateItem(int number, Node *Tree) {
	if(Tree == NULL) {
		cout << "The Number " << number << " has not been found." << endl;
		return Tree;
	}
	
	cout << Tree -> num << endl;
	if(Tree->num == number) {
		cout << "The number " << number << " has been found" << endl;
		return Tree;
	}
	
	if(number > Tree -> num) return locateItem(number, Tree -> right);
	if(number < Tree -> num) return locateItem(number, Tree -> left);
	return Tree;
}


// NAME: insertItem
// INPUT PARAMETERS: number, The number the user wants to insert; Tree, the whole Tree
// OUTPUT: It will return the Tree
// PURPOSE: The function will take a user input and place it inside the tree in the proper spot
//----------------
Node *insertItem(int number, Node *Tree) {
	if( Tree == NULL ) {
		Tree = (Node *)malloc(sizeof(Node));
		Tree -> num = number;
		Tree -> left = NULL;
		Tree -> right = NULL;
		return Tree;
	}
	if( number <= Tree -> num )
		Tree -> left = insertItem(number, Tree -> left);
	else
		Tree -> right = insertItem(number, Tree -> right);
	return Tree;
}


// NAME: deleteItem
// INPUT PARAMETERS: number, The number the user wants to insert; Tree, the whole Tree
// OUTPUT: It will return the Tree
// PURPOSE: The function will take a user input and delete it from the tree
//----------------
Node *deleteItem(int number, Node *Tree) {
	Node *temp = NULL;
	if( Tree  == NULL ) {
		cout << "There number " << number << " does not exist in the Tree." << endl;
		return NULL;
	}

	if( Tree -> num == number) {
		if( Tree -> left == NULL && Tree -> right == NULL) {
			free(Tree);
			return NULL;
		} else {
			if( Tree -> left == NULL ) {
				temp = Tree -> right;
				free(Tree);
				return temp;
			} else if( Tree -> right == NULL ) {
				temp = Tree -> left;
				free(Tree);
				return temp;
			} else {
				temp = Tree -> left;
				Node *current = temp; //Will be the left then far right child.
				Node *parentOfCurrent = temp; //Will be the parent of the left then far right child.
				while(current -> right != NULL) {
					current = current -> right;
				}
				while(parentOfCurrent -> right != current) {
					parentOfCurrent = parentOfCurrent -> right;
				}
				parentOfCurrent -> right = NULL;
				current -> right = Tree -> right;
				current -> left = Tree -> left;
				free(Tree);
				return current;
			}
		}
 	} else {
		if(number <= Tree -> num)
			Tree -> left = deleteItem(number, Tree -> left);
		else
			Tree -> right = deleteItem(number, Tree -> right);
	}
	return Tree;
}


// NAME: printMenu
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will print the menu to the console.
//----------------
void printMenu() {
	cout << "1.) Insert a new node." << endl;
	cout << "2.) Delete an inserted node." << endl;
	cout << "3.) Find a node in the tree." << endl;
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


// NAME: callFunctions
// INPUT PARAMETERS: userInput, The input given by the user; Tree, the whole Tree
// OUTPUT: It will return a Tree
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
Node *callFunctions(int userInput, Node *Tree) {
	int number = 0; //A number the user will input for either finding/deleting/or inputing
	switch( userInput ) {
		case 1:	
			cout << "Please enter a number to add to the tree: ";
			number = getUserNumberChoice();
			Tree = insertItem(number, Tree);
			break;
		case 2:
			cout << "Please enter a number to delete from the tree: ";
			number = getUserNumberChoice();
			Tree = deleteItem(number, Tree);
			break;
		case 3:
			cout << "Please enter a number to search for in the tree: ";
			number = getUserNumberChoice();
			locateItem(number, Tree);
			break;
		default:
			cout << "Wrong output." << endl;
	}
	return Tree;
}
