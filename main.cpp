//
//  main.cpp
//  cs280project1
//
//  Created by parth patel on 2/13/17.
//  Copyright © 2017 Parth. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
#include <regex>
#include "polylex.h"

using namespace std;

string word;
string file; 


bool printToken = false;
bool printSum = false;
bool printStats = false;



int fileCount = 0;

int currentLine = 0;


int currWordLength = 0;

//----------------------------- ERROR HANDLERS -------------------------------
int badString(){
	cout << "DO THE BAD STRING ERROR" << endl;
	exit(0);
}
int poorlyFormedError(string &arg){
	cout << "Argument "  <<  arg << " is poorly formed" << endl;
	exit(0);
}

int notRecognizedError(string &arg){
	cout << "Invalid argument " << arg << endl;
	exit(0);
}

int fileNotFoundError(string &filename){
	cout << "Could not open " << filename << endl;
	exit(0);
}
int tooManyFiles(){
	cout << "Too many file names" << endl;
	exit(0);
}


// ----------------------------- FLAG HANDLER --------------------------------
int flagHandler(string &flag){
	int vMatchCount = 0;
    int sumMatchCount = 0;
    int statsMatchCount = 0;
    string v = "-v";
	string stats = "-stats";
	string sum = "-sum";

	string searchWord = "";

	for(int j = 0; j < flag.length(); j++){
		if(flag[j] == v[j]){
			vMatchCount++;
		} 
		if(stats[j] == flag[j]){
			statsMatchCount++;
		}
		if(sum[j] == flag[j]){
			sumMatchCount++;
		}

	}
	//If the flag is findchar
	if(vMatchCount == 2){
	    if(flag.length() > 2){
	    	return notRecognizedError(flag);
	    } else {
	    	printToken = true;
	    }
	//If the flag is findword
	} else if(sumMatchCount == 4){
		if(flag.length() > 4){
			return notRecognizedError(flag);
		} else {
			printSum = true;
		}
	} else if(statsMatchCount == 6){
		if(flag.length() > 6){
			return notRecognizedError(flag);
		} else {
			printStats = true;
		}
	}
 	else {
		return notRecognizedError(flag);
	}
	return 0;
}
// ------------------------------ FILE HANDLER ---------------------------------
int fileHandler(string &filename){
	if(!fileCount){
		file = filename;
		fileCount++;	
	} else {
		tooManyFiles();
	}
	
	return 0;
}
// ------------------------------ PRINT RESULTS --------------------------------
int printResults(){
	cout << "Total Lines: " << currentLine << endl; 
	cout << "Total tokens: 0" << endl;
	return 0;
}
// ------------------------------- FILE PARSER ---------------------------------
int fileParser(string &filename){
	string line;


	ifstream file (filename);

	if(!file.is_open()) fileNotFoundError(filename);

	int i = 0;

	while(getline(file, line)){
		if(line.length() == 0 && currentLine == 1) currentLine = 0;
		else {
			currentLine++;	
		}
		
		if(!line.length()) continue;
		
	}
	
	return 0;
}
// ------------------------------- STDIN PARSER ---------------------------------
int stdinParser(){
	string line;
	int wordCount = 0;
	int charCount = 0;

	while (getline(cin, line)) {
		if(cin.eof()) break;

	}

	return 0;
}
// ---------------------------------- MAIN -------------------------------------
int main(int argc, const char * argv[]) {

    for(int i = 1; i < argc; i++){

    	word = argv[i];

    	if(word[0] == '-'){
    		flagHandler(word);
		} else {
			fileHandler(word);
		}


    }

    if(!fileCount){
    	stdinParser();
    } else {
    	for(int i = 0; i < fileCount; i++){
    		fileParser(file);
    	}
    }
   //  Token thing = *new Token(ID, "Garbage");
  	// cout<< thing.getType();
    printResults();

    return 0;
}
