#ifndef _TYPO_H
#define _TYPO_H

#define TXT_ARG 1
#define PRINT_USAGE() cout << "\n" << argv[0] << " [input file]" << endl;

#define TYPO 4

#define KLEN 10   		//Keyboard length
#define KHT	4			//Keyboard height

#include <string.h>

typedef struct{  //Structure to define each key.
	char ch;
	int row;
	int col;
	int finger; //1 if index, 2 if mi**le, 3 is ring, 4 is pinky. 
	bool isRight; //True if character is right hand
} Key;

typedef struct{
	Key target;
	Key typo;
	int cost;
} Cell;

enum typo {INSERT, DELETE, SUB, TRAN};
// enum iCond {RC, SAB, SAC, CBS, SH, OH};
// enum dCond {RCH, SP, CSH, COH, FC};
// enum sCond {SFA, KSH, KSFOH, KDFOH};
// enum tCond {SPA, KDH, KSH};

int Dynamic_Programming_Engage(std::string target, std::string modTarget std::string typo);
void Insert(std::string, int);
void Delete(std::string, int);
void Substitution(std::string, int);
void Transpose(std::string, int);

#endif
