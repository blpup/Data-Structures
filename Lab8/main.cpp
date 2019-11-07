#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;



typedef struct NodeB {
	char data;
	NodeB *right,*left;
} Node; //A struct node that holds the values - float and a pointer to the next node.


int getRight(int index);
int getLeft(int index);
void Max_heapify(int index);
int isFull(int number);
void createTree();
void buildHeap();
int getUserSelection(int lowerNum, int greaterNum);
int getUserNumberChoice();
void callFunctions(int userInput, int* running);
void printMenu();

int heapStack[101];
int heapStackMarker = 0;
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


void Max_heapify(int index){
//	cout << index << " index at the top." << endl;
	if(index == -1) return;
	int forChildren = index;
	int leftSibling = getLeft(forChildren);
	int rightSibling = getRight(forChildren);
	int largest = 0;
	int tempHolder = 0;
	int flag = 0;
	cout << heapStack[index] << " parent. "<< heapStack[leftSibling] << " left. " << heapStack[rightSibling] << " right." << endl;
	if( (leftSibling <= heapStackMarker) && (heapStack[leftSibling] > heapStack[index]) ) {
		largest = leftSibling;
	} else {
		largest = index;
	}
	if( (rightSibling <= heapStackMarker) && (heapStack[rightSibling] > heapStack[largest]) ) {
		largest = rightSibling;
	}
	cout << index << " the current. " << endl;
	cout << leftSibling << " the left." << endl;
	cout << rightSibling << " the right." << endl;
	cout << largest << " the largest." << endl;
	cout << "------------" << endl;
	if(largest != index) {
		tempHolder = heapStack[index];
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

int getRight(int index){
	index = 2 * index + 2;
	return index;
}

int getLeft(int index){
	index = 2* index +1;
	return index;
}

int getParent(int index) {
	index = index / 2;
	return index;
}
void createTree() {
	cout << heapStack[0] << endl;
	cout << heapStack[1] << endl;
	cout << heapStack[2] << endl;
	cout << heapStack[3] << endl;
	cout << heapStack[4] << endl;
	cout << heapStack[5] << endl;
	cout << heapStack[6] << endl;
	cout << heapStack[7] << endl;
	cout << heapStack[8] << endl;
	cout << heapStack[9] << endl;
	cout << heapStack[10] << endl;
	cout << heapStack[11] << endl;
	cout << heapStack[12] << endl;
	cout << heapStack[13] << endl;
	cout << heapStack[14] << endl;
}

void buildHeap(){
	int userInput = 0;
	cout << "Enter the values for the heap. Type any negative number to exit." << endl;
	for(;;) {
		if(isFull(heapStackMarker)) {
			cout << "Your heap is now full.";
			break;
		}
		cout << "Please enter a number: ";
		userInput = getUserNumberChoice();
		if(userInput < 0) break;
		heapStack[heapStackMarker] = userInput;
		
		heapStackMarker++;
	}
	Max_heapify(heapStackMarker-1);
	createTree();
}


int isFull(int number) {
	if(number == 50) return 1;
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

// NAME: getUserNumberChoice
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// Side Effect: Will get the user choice for the number for the node
// PURPOSE: The function will error check and return the choice of the user for the number for the node
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

// NAME: callFunctions
// INPUT PARAMETERS: userInput, The input given by the user; Tree, the whole Tree; running, a pointer to running to stop the program
// OUTPUT: It will return a Tree
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
void callFunctions(int userInput, int* running) {
	switch( userInput ) {
		case 1:
			buildHeap();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			exitProgram(running);
			break;
		default:
			cout << "Wrong output." << endl;
	}
}
