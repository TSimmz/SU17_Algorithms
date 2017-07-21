#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <cstdio>
#include <string.h>
#include <unordered_map>
#include "typo.h"
#include "distance.h"

using namespace std;

string typo;
unordered_map<string, int> cost;


int main(int argc, char** argv)
{
	if (argc != 2){
		PRINT_USAGE();
		exit(1);
	}

	ifstream input;
	ofstream output;

	input.open(argv[TXT_ARG]);
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
	
	int num;		// The number of errors
	string target;  // The correct string
	
	while(getline(input,str)
	{
		switch(i)
		{
			case 0: num = atoi(str); break;
			case 1: target = str; break;
			case 2: typo = str; break;
		}
		i++;
	}

	Dynamic_Programming_Engage(target, 0);

	input.close();
	output.close();
	return(0);
}

int Dynamic_Programming_Engage(string target, string modTarget, int i)
{	
	//Check if words match
	if (target == typo.substr(i, string::npos))
		return 0;
		
	//Check if first character matches
	if (target[0] == typo[i])
		Dynamic_Programming_Engage(target.substr(1,string::npos),i++);
	
	//Call functions
	Insert(target, modTarget, i);
	
	Delete(target, i);
	
	Substitution(target, i);
	
	Transpose(target, i);
} 

void Insert(string target, int i)
{
	//Check for null character
	if (target[0] == '\0' || typo[[i] == '\0')
		return;
	
	//Insert cost calculation
	target.insert(0, typo[i]);
	
	//Map assignment
	cost[target] = 2;
	
	Dynamic_Programming_Engage(target, i++);
}

void Delete(string target, int i)
{
	//Check for null character
	
	//Delete cost calculation
	
	//Map assignment
	
	Dynamic_Programming_Engage(target, i++);
}

void Substitution(string target, int i)
{
	//Sub cost calculation
	
	//Map assignment
	
	Dynamic_Programming_Engage(target, i++);
}

void Transpose(string target, int i)
{
	//Check for null character
	
	//Transpose cost calculation
	
	//Map assignment	
	Dynamic_Programming_Engage(target.substr(i, string::npos, i++);
}
