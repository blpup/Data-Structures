// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Max Heap
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------


#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;


int getRight(int index);
int getLeft(int index);
void Max_heapify(int index);
int isFull(int number);
void printTree();
void buildHeap();
int getUserSelection(int lowerNum, int greaterNum);
int getUserNumberChoice();
void callFunctions(int userInput, int* running);
void printMenu();
void deleteRootNode();
int isEmpty();

int heapStack[101]; //the whole heap
int heapStackMarker = 0; //the heap marker
int main(int argc, char **argv)
{
	cout << "Welcome to Lab 8! This program will Max heapify your input." << endl << endl;
	int running = 1; //If the program is still running or not
	while( running ) {
		printMenu();
		int userInput = getUserSelection(1,4); //the user input for function calls
		callFunctions(userInput, &running);
		cout << endl;
	}
	return 0;
}

// NAME: Max_heapify
// INPUT PARAMETERS: index, a number of the last node's index .
// OUTPUT: NONE
// PURPOSE: The function will order the user given heap into a max heap.
//---------------
void Max_heapify(int index){
	if(index == -1) return;
	int leftSibling = getLeft(index); //left child
	int rightSibling = getRight(index); //right child
	int largest = 0; //the largest number's index
	int flag = 0; //a flag that will tell us if we found a new larger element.
	
	if( (leftSibling <= heapStackMarker) && (heapStack[leftSibling] > heapStack[index]) ) {
		largest = leftSibling;
	} else {
		largest = index;
	}
	
	if( (rightSibling <= heapStackMarker) && (heapStack[rightSibling] > heapStack[largest]) ) {
		largest = rightSibling;
	}
	
	if(largest != index) {
		int tempHolder = heapStack[index]; //the temp holder for swaping out the values.
		heapStack[index] = heapStack[largest];
		heapStack[largest] = tempHolder;
		flag = 1;
	}
	
	if(flag == 1) {
		Max_heapify(largest);
	} else {
		Max_heapify(index-1);
	}
	
	return;
}

// NAME: getRight
// INPUT PARAMETERS: index, a number of the current node's index.
// OUTPUT: NONE
// PURPOSE: The function will return the index number of the right child.
//---------------
int getRight(int index){
	index = 2 * index + 2;
	return index;
}

// NAME: getLeft
// INPUT PARAMETERS: index, a number of the current node's index.
// OUTPUT: NONE
// PURPOSE: The function will return the index number of the left child.
//---------------
int getLeft(int index){
	index = 2* index + 1;
	return index;
}


// NAME: printTree
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// PURPOSE: The function will print the heap in a tree order.
//---------------
void printTree() {
	if(isEmpty()) {
		cout << "Your heap is empty please enter values and try again." << endl;
		return;
	}
	int x = 0; // A count that will tell us when to endl after so many elements
	for(int i = 0; i < heapStackMarker; i++) {
		cout << heapStack[i];
		if(i == x){
			cout << endl;
			x = 2*x+2;
		} else {
			cout << " ";
		}
	}
	cout << endl;
}


// NAME: buildHeap
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will build a heap and ++heapStackMarker
// PURPOSE: The function will take user input and build a heap accordingly
//---------------
void buildHeap(){
	cout << "Enter the values for the heap. Type any negative number to exit." << endl;
	for(;;) {
		if(isFull(heapStackMarker)) {
			cout << "Your heap is now full.";
			break;
		}
		cout << "Please enter a number: ";
		int userInput = getUserNumberChoice(); //user input
		if(userInput < 0) break;
		heapStack[heapStackMarker] = userInput;
		
		heapStackMarker++;
	}
	Max_heapify(heapStackMarker-1);
}


// NAME: isFull
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will set the running pointer to 0
// PURPOSE: The function will check if the heap is full
//---------------
int isFull(int number) {
	if(number == 50) return 1;
	return 0;
}


// NAME: isEmpty
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// PURPOSE: The function will check if the heap is empty
//---------------
int isEmpty() {
	if(heapStackMarker == 0) return 1;
	return 0;
} 


// NAME: printMenu
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will print the menu to the console.
//----------------
void printMenu() {
	cout << "1.) Build New Heap." << endl;
	cout << "2.) Delete a Root Node." << endl;
	cout << "3.) Print the heap to the screen." << endl;
	cout << "4.) Exit program." << endl;
}



// NAME: getUserNumberChoice
// INPUT PARAMETERS: NONE
// OUTPUT: userInput, a number the user wants
// Side Effect: Will get the user choice for the number for the node
// PURPOSE: The function will error check and return the choice of the user for the number
//---------------
int getUserNumberChoice() {
	int userInput = 0; //The user input
	int flag = 0; //a flag if true it will continue to run the function
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Please enter a proper number: ";
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if ( flag ) userInput = getUserNumberChoice();
	return userInput;
}

// NAME: getUserSelection
// INPUT PARAMETERS: lowerNum, a lower number for a selection; greaterNum, a greater number for a selection
// OUTPUT: userInput, a number the user wants.
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


// NAME: deleteRootNode
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will subtract one from heapStackMarker I.E deleting a node
// PURPOSE: The function will replace the last node with the top node then delete the last node. 
//---------------
void deleteRootNode() {
	if(isEmpty()) {
		cout << "Your heap is empty please enter values and try again." << endl;
		return;
	}
	heapStack[0] = heapStack[heapStackMarker-1];
	heapStackMarker--;
	Max_heapify(heapStackMarker-1);
}


// NAME: callFunctions
// INPUT PARAMETERS: userInput, The input given by the user; running, a pointer to running to stop the program
// OUTPUT: NONE
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
void callFunctions(int userInput, int* running) {
	switch( userInput ) {
		case 1:
			buildHeap();
			break;
		case 2:
			deleteRootNode();
			break;
		case 3:
			printTree();
			break;
		case 4:
			exitProgram(running);
			break;
		default:
			cout << "Wrong output." << endl;
	}
}
