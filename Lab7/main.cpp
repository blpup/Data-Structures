// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Expression Tree
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------


//----------COLLABORATORS----------
// USED https://scitech105.blogspot.com/2016/03/c-program-for-construction-of.html
// FOR EXPRESSION TREE INPUT. AFTER TRYING FOR HOURS ON TRYING TO DO IT. I FOLLOWED THEIR CODE.
// Making an expression tree is hard 
//USED MERT'S way of coding printInfix and printPostFix


#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;


typedef struct NodeB {
	char data;
	NodeB *right,*left, *prev;
} Node; //A struct node that holds the values - float and a pointer to the next node.


void push(int stack[], int x);
void push(char stack[],char pushToStack) ;
char pop(char stack[]);
int isEmpty(char stack[]);
int isFull(char stack[]);
int isBalance(char stack[]);
void printMenu();
void doCalculations(char userInput[]);
int getPriority(char op);
int errorHandle(char stack[]);
void doMath(char stack[]);
void callFunctions(int userInput, int* running);
void exitProgram(int *running);
int getUserSelection(int lowerNum, int greaterNum);
void insertTree(char stack[]);
void printPrefix(Node *root);
void printInfix(Node *root);



char postfix[100], userInput[100], stackPrimary[100], balanceStack[100];
int additionStack[100];
int stackPrimaryLength = 0, postfixLength = 0, balanceCounter = 0, additionStackLength = 0;
Node *current = NULL; // The current node for adding to the expression tree.
Node *parent = NULL; //The parent node for adding to the expression tree.
Node *root = NULL; //The Expression tree.


int main(int argc, char **argv)
{
	int isRunning = 1; //Check if the user wants to run the program again or not
	cout << "Lab 7 - Single Digit Expression Binary Tree" << endl;
	cout << "Please enter a infix expression (Your expression should be single digit with no spaces): ";
	cin >> userInput;
	doCalculations(userInput);
	while(isRunning) {
		current = NULL;
		parent = NULL;
		root = NULL;
		cout << endl;
		insertTree(postfix);
		printMenu();
		int userChoice = getUserSelection(1,5);
		callFunctions(userChoice,&isRunning);
	}
	cout << root -> data;
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
	int stackCounter = 0; //The counter for the given stack.
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
void push(int stack[], int x) {
	stack[additionStackLength] = x;
	additionStackLength++;
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
	char item = stack[0]; //The current char or item in the stack.
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
int pop(int stack[]) {
	stack[additionStackLength] = '\0';
	additionStackLength--;
	int item = stack[additionStackLength];
	return item;
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
	for(unsigned i = 0; i < strlen(userInput); i++) {
		if((userInput[i] >= 'a' && userInput[i] <='z') || (userInput[i] >= 'A' && userInput[i] <= 'Z') || (userInput[i] >= '0' && userInput[i] <= '9')){
			push(postfix,userInput[i]);
		} else {
			if( userInput[i] == ')' || userInput[i] == '}' || userInput[i] == ']') {

				while( (stackPrimaryLength != -1 ) && (stackPrimary[stackPrimaryLength-1] != '(' && stackPrimary[stackPrimaryLength-1] != '{' && stackPrimary[stackPrimaryLength-1] != '[')) {
					push(postfix,pop(stackPrimary));
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
	}
	for(int i = 0; i <= stackPrimaryLength; i++) {
		if(isEmpty(stackPrimary)) {
			return;
		}
		push(postfix,pop(stackPrimary));
	}
}

// NAME: printMenu
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// SIDE EFFECT: Will print the menu to the screen.
// PURPOSE: The function will print the menu to the screen.
void printMenu() {
	cout << "1.) Print the expression in prefix notation." << endl;
	cout << "2.) Print the expression in infix notation." << endl;
	cout << "3.) Check if it is a complete binary tree." << endl;
	cout << "4.) Calculate the expression given." << endl;
	cout << "5.) Exit the program." << endl;
	cout << "----------" << endl;
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
	}if(isEmpty(stack)) {
		cout << "Your stack is empty. Try again.";
		return 1;
	}
	return 0;
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


// NAME: insertTree
// INPUT PARAMETERS: stack, The infix stack.
// OUTPUT: nothing
// Side-Effect: It will create a expression tree
// PURPOSE: The function will take an infix stack and create a expression tree.
void insertTree(char stack[]) {
  Node * tempNode; //The temp node we will use when adding to the expression tree
  int length = strlen(stack);
  for (int i = length - 1; i >= 0; i--) {
    tempNode = (Node * ) malloc(sizeof(Node));
    tempNode -> data = stack[i];
    tempNode -> left = tempNode -> right = tempNode -> prev = NULL;
    if (root == NULL) {
      root = tempNode;
      current = parent = root;
    } else {
      if (stack[i] == '+' || stack[i] == '-' || stack[i] == '*' || stack[i] == '/') {
        if (parent -> right == NULL) {
          current = tempNode;
          parent -> right = current;
          current -> prev = parent;
          parent = current;
        } else if (parent -> left == NULL) {
          current = tempNode;
          parent -> left = current;
          current -> prev = parent;
          parent = current;
        } else {
          while (parent -> left != NULL) {
            parent = parent -> prev;
          }
          current = tempNode;
          parent -> left = current;
          current -> prev = parent;
          parent = current;
        }
      } else {
        if (parent -> right == NULL) {
          current = tempNode;
          parent -> right = current;
          current -> prev = parent;
        } else if (parent -> left == NULL) {
          current = tempNode;
          parent -> left = current;
          current -> prev = parent;
        } else {
          while (parent -> left != NULL) {
            parent = parent -> prev;
          }
          current = tempNode;
          parent -> left = current;
          current -> prev = parent;
        }
      }
    }
  }
}


// NAME: doMath
// INPUT PARAMETERS: stack, An infix stack
// OUTPUT: Nothing
// PURPOSE: Will do the math calculations
//----------------
void doMath(char stack[]) {
	char* tracker = stack;
	int number2=0, finalNumber=0, temp=0; //The second number in the set of numbers; the final number total; and a temp number;
	while( *tracker != '\0' ) {
		int number1 = finalNumber; // the first number out of the set of numbers
		if(isdigit(*tracker)) {
			temp = *tracker - 48;
			push(additionStack, temp);
		} else {
			number1 = pop(additionStack);
			number2 = pop(additionStack);
			if(*tracker == '+') {
				finalNumber = number1 + number2;
			} else if(*tracker == '-') {
				finalNumber = number1 - number2;
			} else if(*tracker == '*') {
				finalNumber = number1 * number2;
			} else if(*tracker == '/') {
				finalNumber = number1 / number2;
			} else if(*tracker == '%') {
				finalNumber = number1 % number2;
			}
			push(additionStack, finalNumber);
		}
		tracker++;
	}
	cout << "The solution to your expression is " << pop(additionStack) << endl;
}



// NAME: callFunctions
// INPUT PARAMETERS: userInput, The input given by the user; running, a pointer to running to stop the program
// OUTPUT: nothing
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
void callFunctions(int userInput, int* running) {

	switch( userInput ) {
		case 1:
			printPrefix(root);
			cout << endl;
			break;
		case 2:
			printInfix(root);
			cout << endl;
			break;
		case 3:
			cout << "Not Implemented" << endl;
			break;
		case 4:
			doMath(postfix);
			break;
		case 5:
			exitProgram(running);
			break;
		default:
			cout << "Wrong output." << endl;
	}
	return;
}


// NAME: printInfix
// INPUT PARAMETERS: Root, An expression tree
// OUTPUT: NONE
// Side Effect: Will print the infix to the console.
// PURPOSE: The function Will print the infix to the console.
void printInfix(Node *Root) {
	if(Root == NULL) return;
	printInfix(Root->left);
	cout << Root -> data;
	printInfix(Root->right);
}

// NAME: printPrefix
// INPUT PARAMETERS: Root, An expression tree
// OUTPUT: NONE
// Side Effect: Will print the prefix to the console.
// PURPOSE: The function Will print the prefix to the console.
//---------------
void printPrefix(Node *Root) {
	if(Root == NULL) return;
	cout << Root -> data;
	printPrefix(Root->left);
	printPrefix(Root->right);
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
