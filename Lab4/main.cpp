// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Will convert base 10 to any base given by the user
// FOR: CS 2413 Data Structure Section 503
// --------------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

void printWelcome();
void doCalculations(int dividend, int divisor);
int decimalErrorHandler();
int conversionErrorHandler();
int runningErrorHandler();

char numbers[27] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'}; //The list of elements for the base
char finalAnswer[200]; //Holds the final output of 110, 1A, or ..etc

int main(int argc, char **argv)
{
	int decimalNumber = 0; //The decimal number from the user
	int conversionBase = 0; //The conversion number from the user
	int running = 1; // If the user wants to keep running the program
	
	printWelcome();
	
	while( running ) {
		decimalNumber = 0;
		conversionBase = 0;
		while( !decimalNumber ) {
			cout << "Please enter a decimal number: ";
			decimalNumber = decimalErrorHandler();
		}
		
		while( !conversionBase ) {
			cout << "Please enter the conversion base: ";
			conversionBase = conversionErrorHandler();
		}
		
		doCalculations(decimalNumber, conversionBase);
		
		cout << "Your base " << conversionBase << " representation of the number " << decimalNumber << " is: ";
		for(int i = strlen(finalAnswer) - 1; i >= 0; i--){
			cout << finalAnswer[i]; 
		}
		
		cout << endl;
		cout << "Do you want to continue to run the program? Y=1 / N=0: ";
		running = runningErrorHandler();
	}

	
	return 0;
}


// NAME: doCalculatiosn
// INPUT PARAMETERS: dividend, the dividend; divisor, the divisor
// OUTPUT: NONE
// Side-Effect: will add the remainders to the finalAnswer
// PURPOSE: The function computes the remainders from the given dividend and divisor and will push the remainder into the stack.
//----------------
void doCalculations(int dividend, int divisor) {
	int i = 0; //Counter
	int currentNumber =  dividend; //Holds the current dividend. 
	
	while( currentNumber > 0 ) {
		finalAnswer[i] = numbers[currentNumber % divisor];
		currentNumber = currentNumber / divisor;
		i++;
	}
}

// NAME: printWelcome
// INPUT PARAMETERS: NONE
// OUTPUT: NONE
// PURPOSE: Print a small welcome to the screen.
void printWelcome() {
	cout << "Welcome to Lab 4." << endl;
	cout << "This program will take a number and convert it from base 10 to a base of your choice." << endl;
}


// NAME: decimalErrorHandler
// INPUT PARAMETERS: NONE
// OUTPUT: userInput, the number the user inputs
// Side-Effect: NONE
// PURPOSE: The function will handle all the errors for the decimal input.
int decimalErrorHandler() {
	int userInput = 0; //the user input
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Please enter a number." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return 0;
	}
	if( userInput <= 0 ) {
		cout << "Please enter a base of non-zero and non negative." << endl;
		return 0;
	}

	return userInput;
}

// NAME: conversionErrorHandler
// INPUT PARAMETERS: NONE
// OUTPUT: userInput, the number the user inputs
// Side-Effect: NONE
// PURPOSE: The function will handle all the errors for the conversion input.
int conversionErrorHandler() {
	int userInput = 0; //The user input
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Please enter a number." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return 0;
	}
	if( userInput <= 1 || userInput > 28 ) {
		cout << "Please enter a base of 2-28." << endl;
		return 0;
	}

	return userInput;
}


// NAME: runningErrorHandler
// INPUT PARAMETERS: NONE
// OUTPUT: userInput, the number the user inputs
// Side-Effect: NONE
// PURPOSE: The function will handle all the errors for the running input.
int runningErrorHandler() {
	int userInput = 0; //The user input
	int flag = 0;
	cin >> userInput;
	if( cin.fail() ) {
		cout << "Do you want to continue to run the program? Y=1 / N=0: ";
		cin.clear();
		cin.ignore(256, '\n');
		flag = 1;
	}
	if( userInput != 1 && userInput != 0 ) {
		cout << "Do you want to continue to run the program? Y=1 / N=0: ";
		flag = 1;
	}
	if ( flag ) userInput = runningErrorHandler();
	return userInput;
}
