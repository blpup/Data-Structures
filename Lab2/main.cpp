// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Will ask the user for an infix string and it will convert it to postfix
// FOR: CS 2413 Data Structure Section 503
// TEST CASES for Function push:
// 		Test case1: the stack is full
// 			Input: a stack
// 			Expected output: will provide a message saying the stack is full
// 			Actual Output: Your stack is full. Please remove an item from the stack first.
// TEST CASES for Function pop:
// 		Test case1: the stack is empty
// 			Input: a stack
// 			Expected output: will provide a message saying the stack is empty
// 			Actual Output: Your stack is Empty. Please add an item in the stack first.
// TEST CASES for Function peek:
// 		Test case1: the stack is empty
// 			Input: a stack
// 			Expected output: will provide a message saying the stack is empty
// 			Actual Output: Your stack is Empty. Please add an item in the stack first.
// TEST CASES for Function isEmpty:
//		This function has no testable cases. 
// TEST CASES for Function isFull:
//		This function has no testable cases. 
// TEST CASES for Function isBalance:
//		This function has no testable cases. 
// TEST CASES for Function printSteps:
//		This function has no testable cases. 
// TEST CASES for Function printMenu:
//		This function has no testable cases. 
// TEST CASES for Function doCalculations:
//		This function has no testable cases. Since everything is done by other functions
// TEST CASES for Function getPriority:
//		This function has no testable cases. 
// TEST CASES for Function errorHandle:
// 		Test case1: if the user input is over 100
// 			Input: a stack
// 			Expected output: will return a boolean telling another function that there is an error with the provided stack.
// 			Actual Output: a true or false boolean
// 		Test case2: if the stack is empty
// 			Input: a stack
// 			Expected Output: will return a boolean telling another function that there is an error with the provided stack.
// 			Actual output: a true or false boolean
//SPECIAL THANKS TO:
//Used the book for the getPriority function.

//NOTE:"Infix charcter" will repeat a character sometimes because it is printing other calculations happening.
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

void push(char stack[]);
char pop(char stack[]);
char peek(char stack[]);
int isEmpty(char stack[]);
int isFull(char stack[]);
int isBalance(char stack[]);
void printSteps(char stack[], char postFix[], char current);
void printMenu();
void doCalculations(char userInput[]);
int getPriority(char op);
int errorHandle(char stack[]);

char postfix[100], userInput[100], stackPrimary[100], balanceStack[100];
int stackPrimaryLength = 0, postfixLength = 0, balanceCounter = 0;

int main(int argc, char **argv)
{
	int isRunning = 1; //Check if the user wants to run the program again or not
	printMenu();
	while(isRunning) {
		memset( postfix, 0, sizeof(postfix) ); //Clear stacks
		memset( userInput, 0, sizeof(userInput) ); //""
		memset( stackPrimary, 0, sizeof(stackPrimary) ); //""
		memset( balanceStack, 0, sizeof(balanceStack) ); //""
		stackPrimaryLength = 0, postfixLength = 0, balanceCounter = 0;
		cout << "Please enter an infix of characters to make it Postfix: ";
		cin >> userInput;
		doCalculations(userInput);
		cout << "Do you want the program to run again? (Y = 1/ N = 0): ";
		cin >> isRunning;
	}
	return 0;
}

// NAME: push
// INPUT PARAMETERS: stack[], a stack to push to; pushToStack, the data that will be pushed to the stack
// OUTPUT: NONE
// SIDE EFFECT: Will push an item to a stack and it will increment a certain counter depending on the stack.
// PURPOSE: The function will push a new item the a stack.
void push(char stack[],char pushToStack) {
	if(isFull(stack)) {
		cout << "Your stack is full. Please remove an item from the stack first." << endl;
		return;
	}
	
	int stackCounter; //The counter for the given stack.
	if(stack == stackPrimary) {
		stackCounter = stackPrimaryLength;
	} else if (stack == postfix) {
		stackCounter = postfixLength;
	} else if (stack == balanceStack) {
		stackCounter = balanceCounter;
	}
	
	stack[stackCounter] = pushToStack;
	stackCounter++;
	
	if(stack == stackPrimary) {
		stackPrimaryLength = stackCounter;
	} else if (stack == postfix) {
		postfixLength = stackCounter;
	} else if (stack == balanceStack) {
		balanceCounter = stackCounter;
	}
	
	return;
}

// NAME: pop
// INPUT PARAMETERS: stack[], a stack to pop from;
// OUTPUT: A char, the top element from the stack.
// SIDE EFFECT: Will remove the top element from the stack.
// PURPOSE: The function pops out the top most element from the given stack.
char pop(char stack[]) {
	if(isEmpty(stack)) {
		cout << "Your stack is Empty. Please add an item in the stack first." << endl;
		return 0;
	}
	char item; //The current char or item in the stack.
	if(stack == stackPrimary) {
		stack[stackPrimaryLength] = '\0';
		stackPrimaryLength--;
		item = stack[stackPrimaryLength];
	} else if (stack == balanceStack) {
		stack[balanceCounter] = '\0';
		balanceCounter--;
		item = stack[balanceCounter];
	}

	return item;
}

// NAME: peek
// INPUT PARAMETERS: stack[], a stack to peek from;
// OUTPUT: A char, the top element from the stack.
// SIDE EFFECT: NONE
// PURPOSE: The function will look at the top of the stack and return it.
char peek(char stack[]) {
	if(isEmpty(stack)) {
		cout << "Your stack is Empty. Please add an item in the stack first." << endl;
		return 0;
	}
	
	int stackCounter; //The counter for the given stack.
	if(stack == stackPrimary) {
		stackCounter = stackPrimaryLength;
	} else if (stack == postfix) {
		stackCounter = postfixLength;
	} else if (stack == balanceStack) {
		stackCounter = balanceCounter;
	}
	
	return stack[stackCounter];
}

// NAME: isEmpty
// INPUT PARAMETERS: stack[], a stack;
// OUTPUT: An integar, true or false value.
// SIDE EFFECT: NONE
// PURPOSE: The function will check if the stack is empty or not.
int isEmpty(char stack[]) {
	int empty = 1; //Boolean to check if it is empty or not
	
	if ( strlen(stack) != 0 ) {
		empty = 0;
	}
	
	return empty;
}

// NAME: isFull
// INPUT PARAMETERS: stack[], a stack;
// OUTPUT: An integar, true or false value.
// SIDE EFFECT: NONE
// PURPOSE: The function will check if the stack is full or not.
int isFull(char stack[]) {
	int full = 0; //boolean to check if it is full or not
	if( strlen(stack) >= 100 ) {
		full = 1;
	}
	
	return full;
}

// NAME: isBalanced
// INPUT PARAMETERS: stack[], a stack;
// OUTPUT: An integar, true or false value.
// SIDE EFFECT: NONE
// PURPOSE: The function will check if the brackets are even or not and in the right order.
int isBalance(char stack[]) {
	
	for( unsigned i = 0; i < strlen(stack); i++ ) {
		if(userInput[i] == '(' || userInput[i] == '{' || userInput[i] == '[') {
			push(balanceStack, userInput[i]);
		} else if ( userInput[i] == ')' ) {
			if( !isEmpty(balanceStack) ) {
				if(pop(balanceStack) != '(') {
					return 0;
				}
			}
		} else if ( userInput[i] == '}' ) {
			if( !isEmpty(balanceStack) ) {
				if(pop(balanceStack) != '{') {
					return 0;
				}
			}
		} else if ( userInput[i] == ']' ) {
			if( !isEmpty(balanceStack) ) {
				if(pop(balanceStack) != '[') {
					return 0;
				}
			}
		}
	}
	if(balanceCounter > 0) {
		return 0;
	}
	return 1;
}

// NAME: doCalculations
// INPUT PARAMETERS: userInput[], an infix char string;
// OUTPUT: NONE
// SIDE EFFECT: Will sort the userInput into the proper postfix or primaryStack stacks.
// PURPOSE: The function will take the user's input and sort the input into the proper postfix version. 
void doCalculations(char userInput[]) {
	if(errorHandle(userInput)) {
		return;
	}
	cout << " Infix Character          Stack" << setw(50) << "Postfix Expression" << endl;
	for(unsigned i = 0; i < strlen(userInput); i++) {
		if((userInput[i] >= 'a' && userInput[i] <='z') || (userInput[i] >= 'A' && userInput[i] <= 'Z') || (userInput[i] >= '0' && userInput[i] <= '9')){
			push(postfix,userInput[i]);
		} else {
			if( userInput[i] == ')' || userInput[i] == '}' || userInput[i] == ']') {
				
				while( (stackPrimaryLength != -1 ) && (stackPrimary[stackPrimaryLength-1] != '(' && stackPrimary[stackPrimaryLength-1] != '{' && stackPrimary[stackPrimaryLength-1] != '[')) {
					push(postfix,pop(stackPrimary));
					printSteps(stackPrimary, postfix, userInput[i]);
				}
				pop(stackPrimary);
				
			} else if(userInput[i] == '+' || userInput[i] == '-' || userInput[i] == '*' || userInput[i] == '%' || userInput[i] == '/'){
				
				if( getPriority(stackPrimary[stackPrimaryLength-1]) >= getPriority(userInput[i]) ) {
					push(postfix,pop(stackPrimary));
					push(stackPrimary,userInput[i]);
				} else {
					push(stackPrimary,userInput[i]);
				}
				
			} else {
				push(stackPrimary,userInput[i]);
			}
		}
		printSteps(stackPrimary, postfix, userInput[i]);
	}
	for(int i = 0; i <= stackPrimaryLength; i++) {
		if(isEmpty(stackPrimary)) {
			return;
		}
		push(postfix,pop(stackPrimary));
		printSteps(stackPrimary, postfix, userInput[i]);
	}
}

// NAME: printMenu
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// SIDE EFFECT: Will print the menu to the screen.
// PURPOSE: The function will print the menu to the screen.
void printMenu() {
	cout << "This program will take an input of various Infix Characters and return a Postfix Experssion." << endl;
	cout << "An example of this is: A-(B/C+(D%E*F)/G)*H" << endl;
	cout << "This example should return the Postfix Expression of ABC/DEF*%G/+H*-" << endl;
}

// NAME: errorHandle
// INPUT PARAMETERS: stack[], a stack;
// OUTPUT: An integar, a true or false.
// SIDE EFFECT: Print the error message to the screen.
// PURPOSE: The function will check several errors and it will return true if it finds one
int errorHandle(char stack[]) {
	if(!isBalance(stack)) {
		cout << "Your list is not balanced. Try again." << endl;
		return 1;
	}
	if(isFull(stack)) {
		cout << "Your stack is full. Try again." << endl;
		return 1;
	}
	if(isEmpty(stack)) {
		cout << "Your stack is empty. Try again.";
		return 1;
	}
	return 0;
}

// NAME: printSteps
// INPUT PARAMETERS: stack[], the primary stack; postFix[], the postfix stack; current, the current element at that iteration I.E the infix Character;
// OUTPUT: NONE
// SIDE EFFECT: Will print the steps out to the console.
// PURPOSE: The function will print to the console. The purpose is so we know what is happening at what iteration.
void printSteps(char stack[], char postFix[], char current) {
	int lengthOfStack = stackPrimaryLength; //The length of the primary stack. 
	if(stackPrimaryLength == -1) {
		lengthOfStack++;
	}
	cout << " " << current << "                        ";
	for(int i = 0; i < lengthOfStack; i++) {
		cout << stack[i]; 
	} 
	cout << setw(37 - lengthOfStack) << " ";
	for(int j = 0; j < postfixLength; j++ ) {
		cout << postFix[j];
	}
	cout << endl;
}

// NAME: getPriority
// INPUT PARAMETERS: op, an operation char.
// OUTPUT: An integar, a number that will determine if it is greater or lesser.
// SIDE EFFECT: NONE
// PURPOSE: The function will check the operation char and depending on which operation it is, it will return a certain number. This will help tell if the operation is a of higher priority.
int getPriority(char op) {
	if( op == '/' || op == '*'  )
		return 1;
	else if ( op == '+' || op == '-' || op=='%' )
		return 0;
	return -1;
}
