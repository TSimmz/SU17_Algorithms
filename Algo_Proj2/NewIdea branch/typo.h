#ifndef _TYPO_H
#define _TYPO_H

#define TXT_ARG 1
#define PRINT_USAGE() cout << "\n" << argv[0] << " [input file]" << endl;

#define TYPO 4
//#define MAXLEN 100

#define KCOL 10   		//Keyboard columns
#define KROW 4			//Keyboard rows

#include <string>
#include <fstream>

struct Cell{
	int cost; 
	int parent;
};

int MAXLEN;
Cell **m;

enum typo {MATCH, INSERT, DELETE, SUBSTITUTE, TRANSPOSE};

void row_col_init(int);

int Dynamic_Programming_Engage(std::ofstream &, std::string, std::string);

int Match(char, char);
int Insert(char, char, char, bool, bool);
int Delete(char, char, char, char, bool);
int Substitute(char, char);
int Transpose(char, char, char, char, bool);

//void goal_cell(std::string, std::string, int *, int *);
void reconstruct_path(std::ofstream &, std::string, std::string, int, int);

void insert_out(std::ofstream &, std::string, int);
void delete_out(std::ofstream &, std::string, int);
void substi_out(std::ofstream &, std::string, std::string, int, int);
void transp_out(std::ofstream &, std::string, std::string, int, int);

//Structure to define each key.
struct Key{  
	char ch;
	int row;
	int col;
	bool isRight; 	//True if character is right hand
	int finger;		//1 if index, 2 if mi**le, 3 is ring, 4 is pinky. 
};

Key keyboard[KROW][KCOL];

void setKeyboard();
Key getKey(char);
int keyDistance(Key k1, Key k2);

#endif
