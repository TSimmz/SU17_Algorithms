#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "typo.h"
//#include "distance.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2){
		PRINT_USAGE();
		exit(1);
	}

	ifstream input;
	ofstream output;
	
	cout << "\nOpening input file..\n"; 
	input.open(argv[TXT_ARG]);
	
	cout << "\nOpening output file..\n";
	output.open("output.txt");

	if(!input){
		cerr << "\nUnable to open input file.\n";
		exit(1);
	}

	if(!output){
		cerr << "\nUnable to open output file.\n";
		exit(1);
	}
	
	int i = 0;
	string str;
	int cost = 0;
	
	int num;		// The number of errors
	string target;  // The correct string
	string typo;	// The typo string
	
	cout << "\nCreating keyboard..\n";
	setKeyboard();
	
	cout << "\nRetrieving input from file..\n";
	while(getline(input,str))
	{
		switch(i)
		{
			case 0: num = atoi(str.c_str()); break;
			case 1: target = str; break;
			case 2: typo = str; break;
		}
		i++;
	}
	cout << "\nErrors: " << num << endl;
	cout << "Target: " << target << endl;
	cout << "Typo  : " << typo << endl;
	
	cout << "\nCreating cost array..\n";
	MAXLEN = max(target.size(),typo.size()) + 1;
	m = new Cell* [MAXLEN+1];
	for (int i = 0; i < MAXLEN; i++)
		m[i] = new Cell[MAXLEN+1];
	
	cout << "\nDYNAMIC PROGRAMMING ENGAGE!\n";
	cost = Dynamic_Programming_Engage(output, target, typo);
	
	cout << "\nOutputting cost...\n";
	output << cost << endl;
	
	cout << "\nRECONSTRUCTING PATH!\n\n";
	//reconstruct_path(output, target, typo, target.size(), typo.size());
	
	input.close();
	output.close();
	return(0);
}

//************************************************************************
// Initialize rows and columns of the cost array
//************************************************************************
void row_col_init(int i)
{
	m[0][i].cost = m[i][0].cost = i;
	
	m[0][i].parent = (i > 0) ? INSERT : -1;
	m[i][0].parent = (i > 0) ? TRANSPOSE : -1;
}

//************************************************************************
// Algorithm to return the minimum cost of changing target into typo
//************************************************************************
int Dynamic_Programming_Engage(ofstream &op, string target, string typo)
{	
	bool first, last;
	int i, j, k;
	int opt[5];
	
	cout << "\nRow & Col initialization..\n";
	for (i = 0; i < MAXLEN; i++)
	{
		row_col_init(i);
	}
	
	cout << "\nBegginning algorithm..\n";
	for(i = 1; i < target.size(); i++)
	{
		for(j = 1; j < typo.size(); j++)
		{
			first = (i == 0 && j == 0) ? true : false;
			last  = (i == (target.size()-1) || j == (typo.size()-1)) ? true : false;
			
			opt[MATCH] = m[i-1][j-1].cost + Match(target[i], typo[j]);
			opt[INSERT] = m[i][j-1].cost + Insert(typo[j-1], typo[j], typo[j+1], first, last);
			opt[DELETE] = m[i-1][j].cost + Delete(target[i-1], target[i], typo[j-1], typo[j], first);
			opt[SUBSTITUTE] = m[i-1][j-1].cost + Substitute(target[i], typo[j]);
			opt[TRANSPOSE] = m[i-1][j-1].cost + Transpose(target[i-1], target[i], typo[j-1], typo[j], first);
			
			m[i][j].cost = opt[MATCH];
			m[i][j].parent = MATCH;
			
			for(k = INSERT; k <= TRANSPOSE; k++)
			{
				if(opt[k] < m[i][j].cost)
				{
					m[i][j].cost = opt[k];
					m[i][j].parent = k;
				}
			}
		}
		op << m[i][j].cost << endl;
	}
	
	return (m[i][j].cost);
} 

//************************************************************************
// Returns the cost of matching
//************************************************************************
int Match(char s, char t)
{
	// Characters match
	if(s == t)
		return 0;	
}

//************************************************************************
// Returns the cost of insertion
//************************************************************************
int Insert(char s0, char s1, char s2, bool first, bool last)
{
	Key S0 = getKey(s0); // Character before
	Key S1 = getKey(s1); // Character
	Key S2 = getKey(s2); // Character after
	
	//Repeated character
	if(S0.ch == S1.ch)
		return 1;
	
	//Space after key on bottom row
	if(S0.row == 3 &&  S1.ch == ' ')
		return 2;
	
	//Space after something else
	if(S0.row < 3 && S1.ch == ' ')
		return 6;
	
	//Character before a space
	if(S2.ch ==  ' ')
		return 6;
	
	//Before or after another key on same hand
	if(S0.isRight == S1.isRight)
		return keyDistance(S0, S1);
	
	if(S1.isRight == S2.isRight)
		return keyDistance(S1, S2);
	
	//Before or after a key on opposite hand
	return 5;
}

//************************************************************************
// Returns the cost of deletion
//************************************************************************
int Delete(char s1, char s2, char t1, char t2, bool first)
{
	//First character in string
	if(first)
		return 6;
	
	//Target
	Key S1 = getKey(s1); //Character before
	Key S2 = getKey(s2); //Character

	//Typo
	Key T1 = getKey(t1); //Character before
	Key T2 = getKey(t2); //Character
	
	//Repeated character
	if(S2.ch == S1.ch)
		return 1;
	
	//Space
	if(S2.ch == ' ')
		return 3;
	
	//Character after another key on same hand
	if(S1.isRight == S2.isRight)
		return 2;
	
	//Character after space or key on different hand
	return 6;
}

//************************************************************************
// Returns the cost of substitution
//************************************************************************
int Substitute(char s, char t)
{
	Key S = getKey(s); //Target
	Key T = getKey(t); //Typo
	
	//Space for anything or anything for space
	if(S.ch == ' ' || T.ch == ' ') 
		return 6;
	
	//Key for another on same hand
	if(S.isRight == T.isRight)
		return keyDistance(S, T);

	//Key for another on same finger, other hand
	if(S.finger == T.finger)
		return 1;
	
	//Key for another on different finger, other hand
	return 5;
}

//************************************************************************
// Returns the cost of transposition
//************************************************************************
int Transpose(char s1, char s2, char t1, char t2, bool first)
{
	//Target
	Key S1 = getKey(s1); //Character before
	Key S2 = getKey(s2); //Character

	//Typo
	Key T1 = getKey(t1); //Character before
	Key T2 = getKey(t2); //Character
		
	//Space with anything else
	if((S1.ch == T2.ch || S2.ch == T1.ch) && (S1.ch == ' ' || S2.ch == ' '))
		return 3;
	
	//Keys on different hands
	if(T1.isRight != T2.isRight)
		return 1;
	
	//Keys on same hand
	return 2;
}

//************************************************************************
//Reconstructs the path from end to beginning, printing recursively
//************************************************************************
void reconstruct_path(ofstream &op, string s, string t, int i, int j)
{
	switch(m[i][j].parent)
	{
		case -1:
			return;
		case MATCH:
			reconstruct_path(op, s, t, i-1, j-1);
			break;
		case INSERT:
			reconstruct_path(op, s, t, i, j-1);
			insert_out(op, t, j);
			break;
		case DELETE:
			reconstruct_path(op, s, t, i-1, j);
			delete_out(op, s, i);
		case SUBSTITUTE:
			reconstruct_path(op, s, t, i-1, j-1);
			substi_out(op, s, t, i, j);
			break;
		case TRANSPOSE:
			reconstruct_path(op, s, t, i-1, j-1);
			transp_out(op, s, t, i, j);
			break;			
	}
}

//************************************************************************
//Prints the insert data to the output stream
//************************************************************************
void insert_out(ofstream &op, string s, int i)
{
	op << "Insert " << s[i] << " at " << i << endl;
}

//************************************************************************
//Prints the delete data to the output stream
//************************************************************************
void delete_out(ofstream &op, string t, int j)
{
	op << "Delete " << t[j] << " at " << j << endl;
}

//************************************************************************
//Prints the substitution data to the output stream
//************************************************************************
void substi_out(ofstream &op, string s, string t, int i, int j)
{
	if(s[i] != t[j])
		op << "Substitute " << s[i] << " at " << i << endl;
}

//************************************************************************
//Prints the transpose data to the output stream
//************************************************************************
void transp_out(ofstream &op, string s, string t, int i, int j)
{
	op << "Tranpose " << i << "-" << j << endl;
}

//************************************************************************
//Initializes the 'keyboard' of Key structures
//************************************************************************
void setKeyboard()
{
	int row, col, finger;
	bool isRight;
	
	char chars[40] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
					  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
  					  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
		              'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', ' '};

	for(int i = 0; i < 40; i++)
	{
		row = i/10;
		col = i%10;
		
		//Setting character
		keyboard[row][col].ch = chars[i];
		
		//Setting rows and columns
		keyboard[row][col].row = row;
		keyboard[row][col].col = col;
		
		//Setting hand
		keyboard[row][col].isRight = (keyboard[row][col].col > 4) ? true : false;

		//Setting finger -- THIS WILL BE USER DEPENDENT
		if (col > 2 && col < 7){
			keyboard[row][col].finger = 0;
		}else if (col == 2 || col == 7){
			keyboard[row][col].finger = 1;
		}else if (col == 1 || col == 8){
			keyboard[row][col].finger = 2;
		}else if (col == 0 || col == 9){
			keyboard[row][col].finger = 3;
		}
	}
	
	//Manually setting space for Key handling
	keyboard[KROW][KCOL].isRight = false;
	keyboard[KROW][KCOL].finger = 0;
}

//************************************************************************
//Gets the Key struct for the passed in character
//************************************************************************
Key getKey(char ch)
{
	int i, row, col;
	
	for(i = 0; i < (KROW * KCOL); i++)
	{
		row = i/10;
		col = i%10;
		
		if (ch == keyboard[row][col].ch)
			return keyboard[row][col];
	}
}

//************************************************************************
// Finds the distance between two keys - d(k1,k2) = max{|r2-r1|, |c2-c1|}
//************************************************************************
int keyDistance(Key k1, Key k2)
{
    int rowDist = k2.row - k1.row;
    int colDist= k2.col - k1.col;

	rowDist = (rowDist >= 0) ? rowDist : (rowDist * -1);
	colDist = (colDist >= 0) ? colDist : (colDist * -1);

	return (rowDist > colDist) ? rowDist : colDist;
  }