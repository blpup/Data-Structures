#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include<bits/stdc++.h> 
using namespace std;

#define ARRAYSIZE 100

void Create_Graph();
void setArrayLocation(string line);
int getIndexNumber(char letter);
int getWeightFromString(string line);
void printMatrix(int graph[][ARRAYSIZE]);
int Shortest_Distance(int graph[][ARRAYSIZE], char from, char to);
void callFunctions(int userInput, int* running);
int getUserSelection(int lowerNum, int greaterNum);
void printMenu();
void exitProgram(int *running);
char getUserLetterChoice();
void printDistances(int distances[], int sourceNode);

int matrix[ARRAYSIZE][ARRAYSIZE];

char letters[ARRAYSIZE]; // An array of all the letters
char lettersWeights[ARRAYSIZE]; // An array of all the weights
int letterCounter = 0; // A counter to the letters array. Helps to keep track.
int formatFlag = 0;

int main(int argc, char **argv)
{
	for (int i = 0; i < ARRAYSIZE; i++)
		for (int j = 0; j < ARRAYSIZE; j++)
			matrix[i][j] = INT_MAX;
			
			
	Create_Graph();
	if( formatFlag == 1 ) {
		cout << "Invalid File format." << endl;
		return 0;
	} else if(letterCounter == 0) {
		cout << "The file is empty." << endl;
		cout << "Please enter a file with values in it and try again." << endl;
		return 0;
	}
	int running = 1; //If the program is still running or not
	while( running ) {
		cout << "-------------------" << endl;
		printMenu();
		int userInput = getUserSelection(1,3); //the user input for function calls
		cout << "-------------------" << endl;
		callFunctions(userInput, &running);
	}
	return 0;
}


// NAME: Create_Graph
// INPUT PARAMETERS: None
// OUTPUT: None
// Side Effect Output: Will read from the file and add contents to a matrix
// PURPOSE: The function reads from a file data.csv and takes each line and pushes the weights to a matrix.
//----------------
void Create_Graph() {
	string line; //the line from the file
	ifstream file; // Start a file stream
	file.open("./data.csv");

	
	if( file.is_open() ) {
		while ( getline(file, line) ) {
			if(line[1] != ',' && line[3] != ',') {
				formatFlag = 1;
				return;
			}
			setArrayLocation(line);
			int firstIndex = getIndexNumber(line[0]); // the first letter's index.
			int secondIndex = getIndexNumber(line[2]); //the second letter's index
			int weight = getWeightFromString(line); // The data of each line in the file.
			matrix[firstIndex][secondIndex] = weight;
			matrix[secondIndex][firstIndex] = weight;
		}
		file.close();
	} else {
		cout << "File could not be opened. \n";
	}
};


// NAME: setArrayLocation
// INPUT PARAMETERS: line, a string from the file.
// OUTPUT: None
// PURPOSE: The function will check if the letter is already in the array, if not push it to the array.
//----------------
void setArrayLocation(string line) {
	int flags[2] = {0}; //a flag to check if it is already in the array or not
	for(int n = 0; n < letterCounter; n++) {
		if(letters[n] == line[0]) {	flags[0] = 1; }
		if( letters[n] == line[2]) { flags[1] =1;}
	}
	
	if(flags[0] != 1) {
		letters[letterCounter] = line[0];
		letterCounter++;
	}
	
	if( flags[1] != 1) {
		letters[letterCounter] = line[2];
		letterCounter++;
	}
	
}

// NAME: getIndexNumber
// INPUT PARAMETERS: letter, a single letter.
// OUTPUT: None
// PURPOSE: The function will take a letter and loop through the letter array and return the index of that letter.
//----------------
int getIndexNumber(char letter) {
	for(int i = 0; i < letterCounter; i++) {
		if(letters[i] == letter) {
			return i;
		}
	}
	cout << "The Letter's index has not been found" << endl;
	return -1;
}


// NAME: getWeightFromString
// INPUT PARAMETERS: line, a string for the file
// OUTPUT: None
// PURPOSE: The function will take a string and splice the last 4 elements from it to get the weight.
//----------------
int getWeightFromString(string line) {
	int strLength = line.length(); //the length of the string.
	int totalLength = strLength - 4; //the length of the numbers
	int weight; //totalLength but in int form
	string total; //the chars combined into a string format
	for(int i = 0; i < totalLength; i++) {
		total += line[4+i];
	}
	weight = stoi(total);
	return weight;
}


// NAME: printMatrix
// INPUT PARAMETERS: graph, the matrix of the weights
// OUTPUT: None
// PURPOSE: The function will print a matrix to the screen.
//----------------
void printMatrix(int graph[][ARRAYSIZE]){
	cout << " ";
	for(int k = 0; k < letterCounter; k++) {
		cout << setw(5);
		cout << letters[k];
	}
	cout << endl;	
	for( int i = 0; i < letterCounter; i++ ) {
		cout << letters[i];
		for( int j = 0; j < letterCounter; j++ ){
			int weight = graph[i][j]; //the weight at the current node
			if(weight == INT_MAX) {
				weight = 0;
			}
			cout << setw(5);
			cout << weight;
		}
		cout << endl;
	}
}


// NAME: Shortest_Distance
// INPUT PARAMETERS:graph, the matrix of the weights; from, the starting node; to, the going to node
// OUTPUT: None
// PURPOSE: The function will go from the starting node to the finishing node while calculating all the weights
//----------------
int Shortest_Distance(int graph[][ARRAYSIZE], char from, char to){
	int fromIndex = getIndexNumber(from); //the index number from the "from" char
	int toIndex = getIndexNumber(to); // the index number from the "to" char 
	int inQueueNodes[ARRAYSIZE] = {0}; //The nodes that are in the queue to be proccessed
	int distances[ARRAYSIZE]; //the array of distances from the given node to all nodes
	int currentDistance; // currentDistance, the number that is the current distance to a node
	
	for( int i = 0; i < letterCounter; i++ ) {
		distances[i] = INT_MAX;
	}
	
	inQueueNodes[fromIndex] = 1;
	distances[fromIndex] = 0;
	
	while(inQueueNodes[toIndex] == 0) {
		int miniumum = INT_MAX; //the number if it is smaller than the previous
		int m = 0; //m, the index of the new node we are at
		for(int i = 0; i < letterCounter; i++) {
			currentDistance = distances[fromIndex] + graph[fromIndex][i];
			
			if(currentDistance < distances[i] && inQueueNodes[i] == 0 && graph[fromIndex][i] != INT_MAX) {
				distances[i] = currentDistance;
			}
			if( miniumum > distances[i] && inQueueNodes[i] == 0) {
				miniumum = distances[i];
				m = i;
			}
		}
		fromIndex = m;
		inQueueNodes[fromIndex] = 1;
	}
	return distances[toIndex];
}


// NAME: printMenu
// INPUT PARAMETERS: None
// OUTPUT: None
// PURPOSE: The function will print the menu to the console.
//----------------
void printMenu() {
	cout << "1.) Display" << endl;
	cout << "2.) Find the Shortest path From a Node to All Nodes." << endl;
	cout << "3.) Exit program." << endl;
};

// NAME: callFunctions
// INPUT PARAMETERS: userInput, The input given by the user; running, a pointer to running to stop the program
// OUTPUT: nothing
// PURPOSE: The function will take the user input and call the function that the user requested.
//----------------
void callFunctions(int userInput, int* running) {
	int letter; // the index of the letter the user wants to start with
	int distances[letterCounter]; //the distances from the Shortest_Distance function
	switch( userInput ) {
		case 1:
			printMatrix(matrix);
			break;
		case 2:
			for(int i = 0; i < letterCounter; i++) {
				cout << i << ".) " << letters[i] << endl;
			}
			letter = getUserSelection(0,letterCounter-1);
			cout << endl;
			for(int i = 0; i < letterCounter; i++) {
				distances[i] = Shortest_Distance(matrix,letters[letter], letters[i]);
			}
			printDistances(distances, letter);
			break;
		case 3:
			exitProgram(running);
			break;
		default:
			cout << "Wrong output." << endl;
	}
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

// NAME: printDistances
// INPUT PARAMETERS: distances, an array of distances; sourceNode, the source node
// OUTPUT: NONE
// PURPOSE: The function will print the source node -> destination node -> shortest distance.
//---------------
void printDistances(int distances[], int sourceNode) {
	cout << "Source Node " << setw(5) << " Destination Node " << setw(5) << " Shortest Distance from Source Node " << endl;
	for(int i = 0; i < letterCounter; i++) {
		cout << letters[sourceNode] << setw(13) << letters[i] << setw(19) << distances[i] << endl;
	}
}
