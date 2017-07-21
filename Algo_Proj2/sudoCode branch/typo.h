#ifndef _TYPO_H
#define _TYPO_H

#define TXT_ARG 1
#define PRINT_USAGE() cout << "\n" << argv[0] << " [input file]" << endl;

#define KCOL 10   		//Keyboard columns
#define KROW 4			//Keyboard rows

#include <string>
#include <fstream>


//Structure to define each key.
struct Key{  
	char ch;
	int row;
	int col;
	bool isRight; 	//True if character is right hand
	int finger;		//1 if index, 2 if mi**le, 3 is ring, 4 is pinky. 
};

Key keyboard[KROW][KCOL];

//Global Variables
std::string *targetArr;
std::string *typoArr;
std::string typo;
int numProbs;

char firstTarget; //stores first char of target
int numOfCalls=0;


std::unordered_map<std::string, int> cost;
std::unordered_map<std::string, int> insMap;
std::unordered_map<std::string, int> delMap;
std::unordered_map<std::string, int> subMap;
std::unordered_map<std::string, int> transMap;

int typoCost(std::ofstream &, std::string, int);
int getIns(std::string, int);
int getDel(std::string, int, int);
int getSub(std::string, int);
int getTrans(std::string, int);

void setKeyboard();
Key getKey(char);
int keyDistance(Key k1, Key k2);

#endif
