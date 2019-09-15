// --------------------------------------------------------------------------------
// AUTHOR: Arthur Lee Jones
// FILENAME: main.cpp
// SPECIFICATION: For this lab we were given a data from a file that we needed to read from and insert inside a linked list.
//					What I expect my program to do is to ask the user for their inputs to run certain functions and if they want to utilize the file or start from scratch. 
// FOR: CS 2413 Data Structure Section 503

// TEST CASES for Function: addNew
// 		Test case1: test input is odd number
// 			Input: 3
// 			Expected output: should add 3 to the end of the linked list
// 			Actual Output: adds 3 to the end of the linked list
// 		Test case2: test input is even number
// 			Input: 4
// 			Expected output: should add 4 to the end of the linked list
// 			Actual Output: adds 4 to the end of the linked list

// TEST CASES for Function: insertNode
// 		Test case1: test input will add a node after the node contianing 4 and that value will be 2
// 			Input: 3,2,4
// 			Expected output: 2 should be the last on the linked list is the current list is (3,4)
// 			Actual Output: (3,4,2)
// 		Test case2: test input will add a node at the beginning of the linked list and the value will be 2
// 			Input: 1,2, 0
// 			Expected output: should add 2 to the beginning of the linked list
// 			Actual Output: (2, 3, 4, 2)

// TEST CASES for Function: findMaximum
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: Should take the largest number 4
// 			Actual Output: 4

// TEST CASES for Function: findMinimum
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: Should take the smallest number 2
// 			Actual Output: 2

// TEST CASES for Function: findMean
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: Will find the mean of the linked list 2.75
// 			Actual Output: 2.75

// TEST CASES for Function: findMedian
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: Will find the median of the linked list 2.5
// 			Actual Output: 2.5

// TEST CASES for Function: findMode
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: Will find the mode of the linked list. Should output nothing since there is only 1 item of each number in the list.
// 			Actual Output: There is no Mode in the linked list.

// TEST CASES for Function: findRange
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: expected output according to your function design
// 			Actual Output: provide the actual output of the function

// TEST CASES for Function: findRemoveDups
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4,2)
// 			Expected output: It should find and remove any duplicates in the linked list
// 			Actual Output: (2,3,4,2)

// TEST CASES for Function: readFile
// 		Test case1: Nothing to test as it has no editable fields by users
//			Input: This takes no inputs
// 			Expected output: Should take the contents of the file and input them into the linked list.
// 			Actual Output: added data from the file in the linked list.

// TEST CASES for Function: insertInOrder
// 		Test case1: the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4) + sorted data from the file
// 			Expected output: Will sort the list (2,3,4) + sorted data from the file
// 			Actual Output: (2,3,4) + sorted data from the file

// TEST CASES for Function: displayLinkedList
// 		Test case1:the test input is the given data from the test linked list.
//			Input: Will take the linked list (2,3,4) + sorted data from the file
// 			Expected output: should print the sorted list
// 			Actual Output: prints the sorted list

// TEST CASES for Function: deleteNodeTest
// 		Test case1: the test input is the given data from the test linked list.
//			Input:  Will take a mock user input of 3 and a mock user deletion choice of 3. 3 Means the user wants to delete a given node of X. The other 3 is that X.
// 			Expected output: Should find and delete all nodes containing the value 3
// 			Actual Output: deletes all nodes containing 3

// --------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

typedef struct NodeA {
	float num;
	NodeA *next;
} Node; //A struct node that holds the values - float and a pointer to the next node.

Node *head = NULL, *tail = NULL; //Start and End of the linked list.

void addNew(float num);
void readFile();
void insertNode();
void deleteNode();
float findMaximum();
float findMinimum();
void findMean();
void findMedian();
void findMode();
void findRange();
void findRemoveDups();
Node* insertInOrder(Node* head);
void runTests();
void printMenu();
void callFunctions(int userInput);


void insertNodeTest(int userChoice, int nodeValue, int numberAfter);
void deleteNodeTest(int userChoice, int nodeValue);

int main() {
	int choice; //To take user input of the choice they want to do.
	int keepRunning = 1; // boolean to keep for if the user wants to keep the program running.

	while(keepRunning) {
		printMenu();
		cout << "Please enter a number between 1-13: ";
		cin >> choice;
		while(cin.fail()) {
			cout << "Please enter a number:";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> choice;
		}
		callFunctions(choice);
		cout << "Do you want to exit the program?" << endl << " 0.) Yes / 1.) No: ";
		cin >> keepRunning;
	}
	return 0;
};


// NAME: addNew
// INPUT PARAMETERS: num, the number to add in the float value given by user.
// OUTPUT: None
// Side Effect Output: Will add a new Node to the linked list.
// PURPOSE: The function takes a number and adds a new node to the linked list.
//----------------
void addNew(float num) {
	Node *tempPointer; // A pointer that temporary holds the given data to be added.
	tempPointer = (Node *) malloc( sizeof(Node) );
	tempPointer -> num = num;
	tempPointer -> next = NULL;
	if( head == NULL ) {
		head = tempPointer;
	} else { 
		tail -> next = tempPointer;
	}
	
	tail = tempPointer;
};


// NAME: reaadFile
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will read from the file and add the contents to the linked list
// PURPOSE: The function reads from a file data.txt and takes each line and calls addNew() to make new linked list nodes.
//----------------
void readFile() {
	float data; // The data of each line in the file.
	ifstream file; // Start a file stream
	file.open("./data.txt");

	
	if( file.is_open() ) {
		while ( file >> data ) {
			addNew(data);
		}
		file.close();
	} else {
		cout << "File could not be opened. \n";
	}
};


// NAME: insertNode
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will add a new node in the linked list
// PURPOSE: The function asks the user where they want to add a new node. Given the user input of where they want to add it, it will place a new node there.
//----------------
void insertNode() {
	int choice; //To take user input of the choice they want to do.
	float num; // The data of what the user wants to input in the node.
	
	cout << "\nWhere do you want to insert your new node?" << endl;
	cout << " 1.) At the Beginning" << endl;
	cout << " 2.) At the End" << endl;
	cout << " 3.) After the Node Containing the Value X" << endl;
	cout << "Please enter a number between 1-3: ";
	cin >> choice;
	while(cin.fail()) {
		cout << "Please enter a number:";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice;
	}
	if(choice > 3 || choice < 1) {
		cout << "Invalid user input. Please try again" << endl;
		insertNode();
	}
	cout << "Please enter the data value of your new node: ";
	cin >> num;
	while(cin.fail()) {
		cout << "Please enter a number:";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> num;
	}
	
	if( choice == 1 ) {
		Node *tempPointer; // A pointer that temporary holds the given data to be added.
		tempPointer = (Node *) malloc( sizeof(Node) );
		tempPointer -> num = num;
		tempPointer -> next = head;
		head = tempPointer;
	} else if ( choice == 2 ) {
		addNew(num);
	} else if ( choice == 3 ) {
		float x; //The position in the linked list the user wants to place their new node.
		int boolean = 0; //A boolean that will tell if X value has been found or not
		cout << "Please enter the Node's X value to place your number after: ";
		cin >> x;
		
		while(cin.fail()) {
			cout << "Please enter a number:";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> x;
		}
		Node *current = head; //Current points to head, so we can iterate through
		while( current != NULL ) {
			if( current -> num == x) {
				Node *tempPointer; // A pointer that temporary holds the given data to be added.
				tempPointer = (Node *) malloc( sizeof(Node) );
				tempPointer -> num = num;
				tempPointer -> next = current -> next;
				current -> next = tempPointer;
				boolean = 1;
				break;
			}
			current = current -> next;
		}
		if( boolean ) {
			cout << "Your number has been found and deleted." << endl;
		} else {
			cout << "The provided number was not found in the list." << endl;
		}
	}
};


// NAME: deleteNode
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will delete a Node to the linked list.
// PURPOSE: The function asks the user where they want to delete the node. Given the user input where they want to delete it, it will delete that node.
//----------------
void deleteNode() {
	int choice; //To take user input of the choice they want to do.
	cout << "\nWhere do you want to delete the node?" << endl;
	cout << " 1.) At the Beginning" << endl;
	cout << " 2.) At the End" << endl;
	cout << " 3.) After the Node Containing the Value X" << endl;
	cout << "Please enter a number between 1-3: ";
	cin >> choice;
	while(cin.fail()) {
		cout << "Please enter a number:";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice;
	}
	if(choice > 3 || choice < 1) {
		cout << "Invalid user input. Please try again" << endl;
		deleteNode();
	}
	
	if( choice == 1 ) {
		Node *tempPointer = head; // A pointer that temporary holds head
		head = head -> next;
		free(tempPointer);
	} else if ( choice == 2 ) {
		Node *tempPointer = tail, *current = head; // A pointer that temporary holds tail, and the current position.
		while( current != NULL ) {
			if(current -> next == tail) {
				tail = current;
				tail -> next = NULL;
				free(tempPointer);
			}
		current = current -> next;
		}
	} else if ( choice == 3 ) {
		float x; //The node's num value that the user wants to delete.
		int boolean = 0; //A boolean that will tell if X value has been found or not
		Node *current = head, *prev = current; //Current points to head, so we can iterate through and prev is the previous one, so we delete the current one we can reference the prev one and point it to current -> next
		cout << "Please enter the Node's X value to delete: ";
		cin >> x;
		
		while(cin.fail()) {
			cout << "Please enter a number:";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> x;
		}
		
		while( current != NULL ) {
			if( current -> num == x) {
				if(current -> next == NULL) {
					prev -> next = NULL;
					tail = prev;
				} else {
					Node *tempPointer = current; //A temp pointer that references current, so we can free it later when current gets removed from the list.
					prev -> next = current -> next;
					current = prev;
					free(tempPointer);
				}
				boolean = 1;
			}
			prev = current;
			current = current -> next;
		}
		if( boolean ) {
			cout << "Your number has been found and deleted." << endl;
		} else {
			cout << "The provided number was not found in the list." << endl;
		}
	}
};


// NAME: findMaximum
// INPUT PARAMETERS: None
// OUTPUT: Will return the largest number in the linked list.
// PURPOSE: The function will find the largest number in the linked list.
//----------------
float findMaximum() {
	float maximum = head -> num; //We set the maximum to the first number.
	Node *current = head; //Current points to head, so we can iterate through.
	
	while( current != NULL ) {
		if(current -> num > maximum) {
			maximum = current -> num;
		}
		current = current -> next;
	}
	return maximum;
};


// NAME: findMaximum
// INPUT PARAMETERS: None
// OUTPUT: Will return the smallest number in the linked list.
// PURPOSE: The function will find the smallest number in the linked list.
//----------------
float findMinimum() {
	float minimum = head -> num; //We set the minimum to the first number.
	Node *current = head; //Current points to head, so we can iterate through.
	
	while( current != NULL ) {
		if(current -> num < minimum) {
			minimum = current -> num;
		}
		current = current -> next;
	}
	return minimum;
};


// NAME: findMean
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will post the results to the console.
// PURPOSE: The function will calculate the mean of the linked list.
//----------------
void findMean() {
	float dividend = 0, divisor = 0, mean = 0; //The dividend and divisor for the mean operation and the mean variable.
	Node *current = head; //Current points to head, so we can iterate through.
	
	while( current != NULL ) {
		dividend += current -> num;
		current = current -> next;
		divisor++;
	}
	mean = dividend/divisor;
	cout << "The Mean is " << mean << "." << endl;
};


// NAME: findMedian
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will post the results to the console.
// PURPOSE: The function will calculate the median of the linked list.
//----------------
void findMedian() {
	int total = 0; //The total number of items in the linked list
	float median = 0; // The median value 
	Node *current = head; //Current points to head, so we can iterate through.
	while( current != NULL ) {
		total++;
		current = current -> next;
	}
	if(total % 2 == 0) {
		current = head;
		for( int i = 1; i < (total/2); i++) {
			current = current -> next;
		}
		median = (current -> num + current -> next -> num) /2;
	} else {
		current = head;
		for( int i = 1; i < (total/2); i++) {
			current = current -> next;
		}
		median = current -> num;
	}
	cout << "The Median is " << median << "." << endl;
};


// NAME: findMode
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will post the results to the console.
// PURPOSE: The function will calculate the mode of the linked list.
//----------------
void findMode() {
	Node *current = head; //Current points to head, so we can iterate through.
	int maxTotal = 1, tempTotal = 0; //maxTotal is the highest repeating item in the linked list. tempTotal is the total of the repeating items. We set maxTotal to 1 because of all items only have 1 then there is no Mode.
	float mode = current -> num; //We set the mode to the first item. 
	
	while( current -> next != NULL ) {
		if(current -> num == current -> next -> num) {
			tempTotal++;
		} else {
			if(tempTotal > maxTotal) {
				maxTotal = tempTotal;
				mode = current -> num;
			}
			tempTotal = 0;
		}
		current = current -> next;
	}
	
	if( maxTotal == 1) {
		cout << "There is no Mode in the linked list." << endl;
	} else {
		cout << "The Mode is " << mode << "." << endl;
	}
	
};


// NAME: findRange
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will post the results to the console.
// PURPOSE: The function will calculate the range of the linked list.
//----------------
void findRange() {
	float maximum, minimum, range; // The greatest and lowest numbers, and range variables for the range.
	maximum = findMaximum();
	minimum = findMinimum();
	range = maximum - minimum;
	cout << "The Range number is " << range << "." << endl;
};


// NAME: findRemoveDups
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will remove any duplicates in the linked list.
// PURPOSE: The function will search through the linked list and remove any duplicates it finds.
//----------------
void findRemoveDups() {
	Node *first, *second, *dup; //the first element, the second element after it, and the dup if it was found.
	first = head;
	
	while((first != NULL) && (first -> next != NULL)) {
		second = first;
		
		while( second -> next != NULL ){
			if( first -> num == second -> next -> num) {
				dup = second -> next;
				second -> next = second -> next -> next;
				free(dup);
			} else {
				second = second -> next;
			}
			
		}
		first = first -> next;
	}
};


// NAME: insertInOrder
// INPUT PARAMETERS: head pointer
// OUTPUT: returns the new head
// Side Effect Output: Will order the list in ascending order
// PURPOSE: The function will order the primary list 
//----------------
Node* insertInOrder(Node* head) {
	if( head == NULL ) {
		cout << "The given list is empty please create a new node." << endl;
		insertNode();
	}
	
    Node *current, *prev, *after; //The current, prev, and after positions in the Linked list.
    current = head;
    head = NULL;
 
    while(current != NULL) {
        after = current;
        current = current->next;
		
        if ( head != NULL ) {
            if( after->num > head->num ) {
                prev = head;
                while ( (prev->next != NULL) && (after->num> prev->next->num) ) {
                    prev = prev->next;
                }
                after -> next = prev -> next;
                prev -> next = after;
            } else {
                after -> next = head;
                head = after ;
            }
        } else {
            after -> next = NULL;
            head = after ;
        }
    }
    return head;
};


// NAME: displayLinkedList
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will display the linked list, so people know what it looks like after any operation.
//----------------
void displayLinkedList() {
	Node *current = head;  //Current points to head, so we can iterate through.
	while( current != NULL ) {
		cout << current -> num << ", ";
		current = current -> next;
	}
	cout << endl;
}


// NAME: runTests
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will post test results to the console.
// PURPOSE: The function will run all the tests.
//----------------
void runTests() {
	if(head != NULL) {
		cout << "Please run tests at the start of the program" << endl;
		return;
	}
	cout << "Tests are running..." << endl << endl;
	
	cout << "Insert node tests..." << endl;
	addNew(3);
	addNew(4);
	insertNodeTest(3,2,4);
	insertNodeTest(1,2,0);
	displayLinkedList();
	cout << endl;
	
	cout << "Find Maximum tests..." << endl;
	float maximum; //The greatest number in the linked list
	maximum = findMaximum();
	cout << "The Maximum number is " << maximum << "." << endl;
	cout << endl;
	
	cout << "Find Minimum tests..." << endl;
	float minimum; //The lowest number in the linked list
	minimum = findMinimum();
	cout << "The Minimum number is " << minimum << "." << endl;
	cout << endl;
	
	cout << "Find Mean tests..." << endl;
	findMean();
	cout << endl;
	
	cout << "Find Median tests..." << endl;
	head = insertInOrder(head);
	findMedian();
	cout << endl;
	
	cout << "Find Mode tests..." << endl;
	head = insertInOrder(head);
	findMode();
	cout << endl;
	
	cout << "Find Range tests..." << endl;
	findRange();
	cout << endl;
	
	cout << "Find Remove Duplicates tests..." << endl;
	findRemoveDups();
	displayLinkedList();
	cout << endl;
	
	cout << "Get list from file tests..." << endl;
	readFile();
	cout << endl;
	
	cout << "Insert In Order tests..." << endl;
	head = insertInOrder(head);
	cout << endl;
	
	cout << "Display Linked List tests..." << endl;
	displayLinkedList();
	cout << endl;
	
	cout << "Delete node tests..." << endl;
	deleteNodeTest(3,3);
	displayLinkedList();
	
	cout << endl;
	
	cout << "Clearing test..." << endl;
	Node *current = head; //the current head hash
	Node *tempPointer; // A pointer that temporary holds the next value
	while( current != NULL ) {
		tempPointer = current -> next;
		free(current);
		current = tempPointer;
	}
	head = NULL, tail = NULL;
};


// NAME: printMenu
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will print the menu to the console.
//----------------
void printMenu() {
	cout << "\nEnter a number to access an option." << endl;
	cout << " 1.) Insert" << endl;
	cout << " 2.) Delete" << endl;
	cout << " 3.) Find Maximum" << endl;
	cout << " 4.) Find Minimum" << endl;
	cout << " 5.) Find Mean" << endl;
	cout << " 6.) Find Median" << endl;
	cout << " 7.) Find Mode" << endl;
	cout << " 8.) Find Range" << endl;
	cout << " 9.) Find and Remove Duplicates" << endl;
	cout << " 10.) Insert In Order" << endl;
	cout << " 11.) Run Tests" << endl;
	cout << " 12.) Display Linked List" << endl;
	cout << " 13.) Get Linked list from file" << endl;
};


// NAME: callFunctions
// INPUT PARAMETERS: The input given by the user 
// OUTPUT: None
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
void callFunctions(int userInput) {
	if(userInput > 13 || userInput < 1) {
		cout << "Invaild Input. Try again." << endl;
		return;
	}
	if(head == NULL && userInput != 10 && userInput != 1 && userInput != 13 && userInput != 11) {
		cout << "There is nothing to read from the list. Please either add a new node or read from the file." << endl;
		return;
	}
	
	switch(userInput){
		case 1:
			insertNode();
			break;
		case 2:
			deleteNode();
			break;
		case 3:
			float maximum; //The greatest number in the linked list
			maximum = findMaximum();
			cout << "The Maximum number is " << maximum << "." << endl;
			break;
		case 4:
			float minimum; //The lowest number in the linked list
			minimum = findMinimum();
			cout << "The Minimum number is " << minimum << "." << endl;
			break;
		case 5:
			findMean();
			break;
		case 6:
			head = insertInOrder(head);
			findMedian();
			break;
		case 7:
			head = insertInOrder(head);
			findMode();
			break;
		case 8:
			findRange();
			break;
		case 9:
			findRemoveDups();
			break;
		case 10:
			head = insertInOrder(head);
			break;
		case 11:
			runTests();
			break;
		case 12:
			displayLinkedList();
			break;
		case 13:
			readFile();
			break;
		default:
			cout << "Invaild Input. Try again." << endl;
			break;
	}
}





//SAME FUNCTIONS WITH TESTABLE ATTRIBUTES

// NAME: insertNodeTest
// INPUT PARAMETERS: userChoice, A mock user choice for testing. nodeValue, a mock value that could be inputed by the user. numberAfter, a mock value that represents the add after x.
// OUTPUT: None
// Side Effect Output: Will add a new node in the linked list
// PURPOSE: The function asks the user where they want to add a new node. Given the user input of where they want to add it, it will place a new node there.
//----------------
void insertNodeTest(int userChoice, int nodeValue, int numberAfter) {
	if( userChoice == 1 ) {
		Node *tempPointer; // A pointer that temporary holds the given data to be added.
		tempPointer = (Node *) malloc( sizeof(Node) );
		tempPointer -> num = nodeValue;
		tempPointer -> next = head;
		head = tempPointer;
	} else if ( userChoice == 2 ) {
		addNew(nodeValue);
	} else if ( userChoice == 3 ) {
		Node *current = head; //Current points to head, so we can iterate through
		while( current != NULL ) {
			if( current -> num == numberAfter) {
				Node *tempPointer; // A pointer that temporary holds the given data to be added.
				tempPointer = (Node *) malloc( sizeof(Node) );
				tempPointer -> num = nodeValue;
				tempPointer -> next = current -> next;
				current -> next = tempPointer;
				break;
			}
			current = current -> next;
		}
	}
};

// NAME: deleteNodeTest
// INPUT PARAMETERS: userChoice, A mock user choice for testing. numberAfter, a mock value that represents the delete after x.
// OUTPUT: None
// Side Effect Output: Will delete a Node to the linked list.
// PURPOSE: The function asks the user where they want to delete the node. Given the user input where they want to delete it, it will delete that node.
//----------------
void deleteNodeTest(int userChoice, int nodeValue) {
	if( userChoice == 1 ) {
		Node *tempPointer = head; // A pointer that temporary holds head
		head = head -> next;
		free(tempPointer);
	} else if ( userChoice == 2 ) {
		Node *tempPointer = tail, *current = head; // A pointer that temporary holds tail, and the current position.
		while( current != NULL ) {
			if(current -> next == tail) {
				tail = current;
				tail -> next = NULL;
				free(tempPointer);
			}
		current = current -> next;
		}
	} else if ( userChoice == 3 ) {
		int boolean = 0; //A boolean that will tell if X value has been found or not
		Node *current = head, *prev = current; //Current points to head, so we can iterate through and prev is the previous one, so we delete the current one we can reference the prev one and point it to current -> next
		while( current != NULL ) {
			if( current -> num == nodeValue) {
				if(current -> next == NULL) {
					prev -> next = NULL;
					tail = prev;
				} else {
					Node *tempPointer = current; //A temp pointer that references current, so we can free it later when current gets removed from the list.
					prev -> next = current -> next;
					current = prev;
					free(tempPointer);
				}
				boolean = 1;
			}
			prev = current;
			current = current -> next;
		}
		if( boolean ) {
			cout << "Your number has been found and deleted." << endl;
		} else {
			cout << "The provided number was not found in the list." << endl;
		}
	}
};
