// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: Will enqueue and dequeue items from 3 different priorities until 20 items have exited or an error occurs
// FOR: CS 2413 Data Structure Section 503
// TEST CASES for Function enqueue:
// 		Test case1: the stack is full
// 			Input: a full stack (with other correct inputs)
// 			Expected output: will provide a message saying the stack is full
// 			Actual Output: There is an Overflow in a Queue.
// TEST CASES for Function dequeue:
// 		Test case1: the stack is empty
// 			Input: an empty stack (with other correct inputs)
// 			Expected output: will provide a message saying the stack is empty
// 			Actual Output: There is an Underflow in a Queue.
// TEST CASES for Function isEmpty:
// 		Test case1: if provided negative numbers (-1, -1)
// 			Input: two numbers both negative
// 			Expected output: should output 1 if they are both equal or 0 if they are not
// 			Actual Output: Outputs 1
// TEST CASES for Function isFull:
// 		Test case1: if provided positive numbers (1,3)
// 			Input: two numbers both positive
// 			Expected output: should output 1 if head is 0 and tail is 10 or tail == to head -1 or if head is 10 and tail is 0, else it will return 0
// 			Actual Output: outputs 0
// TEST CASES for Function displayStatus:
//			Is a basic print statement and cannot be tested.
// TEST CASES for Function getRanNumber:
// 		Test case1: two bound numbers (100, 899)
// 			Input: two numbers 
// 			Expected output: should provide a random number between both bounds
// 			Actual Output: Generates a random number between 100-999
// --------------------------------------------------------------------------------


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

int getRandNumber(int min, int max);
void displayStatus(int number, int priority, int removeOrAdd);
int isEmpty(int head, int tail);
int isFull(int head, int tail);
void dequeue(int queue[], int* head, int* tail);
void enqueue(int queue[], int* head, int* tail, int randNum);
int getTwoOrFour();

int totalExit = 0; //the amount of total items that exited the program
int exitProgram = 0; //a flad that will tell the program to stop

int main()
{
	int firstQueue[11] = {0}, secondQueue[11] = {0}, thirdQueue[11] = {0}; // The first, second, and third queue arrays
	int firstQueueHead = 0, secondQueueHead = 0, thirdQueueHead = 0; // The first, second, and third head pointers for the queues
	int firstQueueTail = 0, secondQueueTail = 0, thirdQueueTail = 0; // The first, second, and third tail pointers for the queues
	
	srand(time(NULL));
	for(int i = 0; i < 6; i++) { // index i
		int priority = getRandNumber(1, 3); // A random number between 1-3
		int randNum = getRandNumber(100, 899); // A random number between 100-899
		switch(priority) {
			case 1:
				enqueue(firstQueue, &firstQueueHead, &firstQueueTail, randNum);
				break;
			case 2:
				enqueue(secondQueue, &secondQueueHead, &secondQueueTail, randNum);
				break;
			case 3:
				enqueue(thirdQueue, &thirdQueueHead, &thirdQueueTail, randNum);
				break;
		}
		displayStatus(randNum, priority, 0);
	}
	while(!exitProgram) {
		int amountToRemove = getTwoOrFour(); // A random number of 2 or 4
		for(int i = 0; i < amountToRemove; i++) { //index i
			if( !isEmpty(firstQueueHead, firstQueueTail) ) {
				
				displayStatus(firstQueue[firstQueueHead], 1, 1);
				dequeue(firstQueue, &firstQueueHead, &firstQueueTail);
				
			} else if( !isEmpty(secondQueueHead, secondQueueTail) ) {
				
				displayStatus(secondQueue[secondQueueHead], 2, 1);
				dequeue(secondQueue, &secondQueueHead, &secondQueueTail);
				
			} else if( !isEmpty(thirdQueueHead, thirdQueueTail) ) {
				
				displayStatus(thirdQueue[thirdQueueHead], 3, 1);
				dequeue(thirdQueue, &thirdQueueHead, &thirdQueueTail);
				
			} else {
				cout << "All the Queues have been emptied before 20 could exit." << endl;
				exitProgram = 0;
			}
			if(exitProgram)
				break;
		}
		if(exitProgram)
			break;
		cout << "3 items will be added to the queue." << endl;
		for(int i = 0; i < 3; i++) { //index i
			int priority = getRandNumber(1, 3); // A random number between 1-3
			int randNum = getRandNumber(100, 899); // A random number between 100-899
			if( exitProgram )
				break;
			switch(priority) {
				case 1:
					enqueue(firstQueue, &firstQueueHead, &firstQueueTail, randNum);
					break;
				case 2:
					enqueue(secondQueue, &secondQueueHead, &secondQueueTail, randNum);
					break;
				case 3:
					enqueue(thirdQueue, &thirdQueueHead, &thirdQueueTail, randNum);
					break;
			}
			displayStatus(randNum, priority, 0);
		}
	}
	return 0;
}


// NAME: enqueue
// INPUT PARAMETERS: queue, a list of numbers; head, a number that points to the current element; tail, a number that points to the last added item; randNum, a random number to be added to the array
// OUTPUT: None
// Side Effect: Will add a random number to a given queue
// PURPOSE: The function adds numbers to a queue
//---------------
void enqueue(int queue[], int* head, int* tail, int randNum) {
	if( isFull(*head, *tail) ) {
		cout << "There is an Overflow in a Queue." << endl;
		exitProgram = 1;
		return;
	}
	
	queue[*tail] = randNum;
	if( *tail == 10 ) {
		*tail = 0;
	} else {
		*tail = *tail + 1;
	}
}


// NAME: dequeue
// INPUT PARAMETERS: queue, a list of numbers; head, a number that points to the current element; tail, a number that points to the last added item
// OUTPUT: None
// Side Effect: Will remove a number from a queue
// PURPOSE: The function removes a number from the queue
//---------------
void dequeue(int queue[], int* head, int* tail) {
	if( isEmpty(*head, *tail) ) {
		cout << "There is an Underflow in a Queue." << endl;
		exitProgram = 1;
		return;
	}
	
	if( *head == 10 ) {
		*head = 0;
	} else {
		*head = *head + 1;
	}
	
	totalExit++;
	if( totalExit == 20 ) {
		cout << "20 items have exited the program. The program will now terminate." << endl;
		exitProgram = 1;
	}
}


// NAME: isFull
// INPUT PARAMETERS: head, a number that points to the current element; tail, a number that points to the last added item
// OUTPUT: A boolean value of true (1) or (0)
// PURPOSE: The function checks if a queue is full
//---------------
int isFull(int head, int tail) {
	if( (head == 0 && tail == 10) || (tail == head -1) || (head == 10 && tail == 0) )
		return 1;
	return 0;
}


// NAME: isEmpty
// INPUT PARAMETERS: head, a number that points to the current element; tail, a number that points to the last added item
// OUTPUT: A boolean value of true (1) or false (0)
// PURPOSE: The function checks if the queue is empty
//---------------
int isEmpty(int head, int tail) {
	if( head == tail )
		return 1;
	return 0;
}


// NAME: displayStatus
// INPUT PARAMETERS: number, the number that is exiting; priority, the priority of that number; removeOrAdd, a boolean value that will tell us if it's being removed or added
// OUTPUT: None
// Side Effect: Will print to the console
// PURPOSE: The function will display what has been removed and what has not been removed
//---------------
void displayStatus(int number, int priority, int removeOrAdd) {
	if( removeOrAdd == 0 ) {
		cout << "The number " << number << " has been added to queue #" << priority <<"." << endl;
	} else {
		cout << "The number " << number << " has been removed from queue #" << priority <<"." << endl;
	}
}

// NAME: getRandNumber
// INPUT PARAMETERS: min, the low end number to iterate through; max, the high end number to iterate through
// OUTPUT: A random number depending on what params are given
// PURPOSE: The function will generate a random number
//---------------
int getRandNumber(int min, int max) {
	return rand() % max + min;
}


// NAME: getTwoOrFour
// INPUT PARAMETERS: None
// OUTPUT: A value of 2 or 4
// PURPOSE: The function will provide a random value of either 2 or 4 value for the amount of items should be removed.
//---------------
int getTwoOrFour() {
	int val = 0; //The value 2 or 4. This tells the program how many items need to be removed
	int random = getRandNumber(0,2); // get a random number from 0-1 helps pick a random number 2 or 4
	( random == 0 ) ?  val = 2 : val = 4;
	cout << val << " items will be removed from the queue." << endl;
	return val;
}
