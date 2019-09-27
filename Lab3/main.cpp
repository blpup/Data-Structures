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

int totalExit = 0;
int exitProgram = 0;

int main(int argc, char **argv)
{
	int firstQueue[11] = {0}, secondQueue[11] = {0}, thirdQueue[11] = {0};
	int firstQueueHead = 0, secondQueueHead = 0, thirdQueueHead = 0;
	int firstQueueTail = 0, secondQueueTail = 0, thirdQueueTail = 0;
	
	srand(time(NULL));
	for(int i = 0; i < 6; i++) {
		int priority = getRandNumber(1, 3);
		int randNum = getRandNumber(100, 899);
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
		int amountToRemove = getTwoOrFour();
		for(int i = 0; i < amountToRemove; i++) { 
			if(!isEmpty(firstQueueHead, firstQueueTail)) {
				
				displayStatus(firstQueue[firstQueueHead], 1, 1);
				dequeue(firstQueue, &firstQueueHead, &firstQueueTail);
				
			} else if(!isEmpty(secondQueueHead, secondQueueTail)) {
				
				displayStatus(secondQueue[secondQueueHead], 2, 1);
				dequeue(secondQueue, &secondQueueHead, &secondQueueTail);
				
			} else if(!isEmpty(thirdQueueHead, thirdQueueTail)) {
				
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
		for(int i = 0; i < 3; i++) {
			int priority = getRandNumber(1, 3);
			int randNum = getRandNumber(100, 899);
			if(exitProgram)
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

void enqueue(int queue[], int* head, int* tail, int randNum) {
	if( isFull(*head, *tail) ) {
		cout << "There is an Overflow in a Queue." << endl;
		exitProgram = 1;
		return;
	}
	
	
	queue[*tail] = randNum;
	
	if(*tail == 10) {
		*tail = 0;
	} else {
		*tail = *tail + 1;
	}
}

void dequeue(int queue[], int* head, int* tail) {
	if( isEmpty(*head, *tail) ) {
		cout << "There is an Underflow in a Queue." << endl;
		exitProgram = 1;
		return;
	}
	
	*head = *head + 1;
	totalExit++;
	if(totalExit == 20) {
		cout << "20 items have exited the program. The program will now terminate." << endl;
		exitProgram = 1;
	}
}

int isFull(int head, int tail) {
	if((head == 0 && tail == 10) || (tail == head -1) || (head == 10 && tail == 0))
		return 1;
	return 0;
}

int isEmpty(int head, int tail) {
	if(head == tail)
		return 1;
	return 0;
}

void displayStatus(int number, int priority, int removeOrAdd) {

	if(removeOrAdd == 0) {
		cout << "The number " << number << " has been added to queue #" << priority <<"." << endl;
	} else {
		cout << "The number " << number << " has been removed from queue #" << priority <<"." << endl;
	}
}

int getRandNumber(int min, int max) {
	return rand() % max + min;
}

int getTwoOrFour() {
	int val = 0; //The value 2 or 4. This tells the program how many items need to be removed
	int random = getRandNumber(0,2); // get a random number from 0-1 helps pick a random number 2 or 4
	( random == 0 ) ?  val = 2 : val = 4;
	cout << val << " items will be removed from the queue." << endl;
	return val;
}
