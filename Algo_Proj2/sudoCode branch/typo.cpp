#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "typo.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2){
		PRINT_USAGE();
		exit(1);
	}


	ifstream input;			// Input stream
	ofstream output;		// Output stream
	ofstream tmpOutput;		// Temp output stream

	setKeyboard();

	input.open(argv[TXT_ARG]);
	output.open("output.txt");
	tmpOutput.open("tmpOutput.txt");

	// Test the streams - exit if no good
	if(!input){
		cerr << "\nUnable to open input file.\n";
		exit(1);
	}

	
	if(!output){
		cerr << "\nUnable to open output file.\n";
		exit(1);
	}

	if(!tmpOutput)
	{
		cerr << "\nUnable to open temp output file.\n";
		exit(1);
	}

	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	string str;

	cout << "\nGetting all input..\n";
	while(getline(input,str))
	{
		switch(i)
		{
			case 0:
				cout << "\nGetting number of problems..\n";
				numProbs = atoi(str.c_str());
				targetArr = new string[numProbs];
				typoArr = new string[numProbs];
				i++;
				break;
			case 1:
				cout << "Getting target..\n";
				targetArr[j++] = str;
				i++;
				break;
			case 2:
				 cout << "Getting typo..\n";
				typoArr[k++] = str;
				i--;
				m++;
				break;
		}
		input.ignore(1,'\n');
	}
	
	cout << "\nStarting algorithm...\n";	
	for(int i = 0; i < numProbs; i++)
	{
		int cost; 
		typo = typoArr[i];
		
		cout << "\nCost run..\n";
		cost = typoCost(tmpOutput, targetArr[i], 0);	// Uses tmpOutput stream to get cost first
		output << cost << endl;							// Outputs cost

		cout << "\nOutput run..\n";
		cost = typoCost(output, targetArr[i], 0);		// Runs algo again to output to stream
		output << endl;									// Outputs a blank line
	}

	cout << "\nClosing and flushing..\n";
	//Close streams and flush memory used by arrays
	input.close();
	output.close();
	tmpOutput.close();
	
	system("rm tmpOutput.txt");

	return 0;
}

//***************************************************************************
// typoCost - recursive function in order to calculate the minimum cost
//			  to transform the target to typo
//***************************************************************************
int typoCost(ofstream &output, string target, int iterTypo){
  int insertCost, delCost, subCost, transCost;
  int lowestCost=0;
  int snip=1;

  if(target.size() == 0){ //Base case
    return lowestCost;
  }

  if(iterTypo>typo.size()){
	return lowestCost;
	}

  //Memoized code, checks map frst. 0(n) is worst case. Average is O(1).
  // Passes lowest cost as 0 if characters match
  if(target[0] != typo[iterTypo]){ 
		//Calculate the cost for each of the modifications
		insertCost = (insMap.find(target) != insMap.end()) ? insMap.at(target) : getIns(target,iterTypo);
		delCost = (delMap.find(target) != delMap.end()) ? delMap.at(target) : getDel(target, iterTypo, numOfCalls);
		subCost = (subMap.find(target) != subMap.end()) ? subMap.at(target) : getSub(target, iterTypo);
		transCost = (transMap.find(target) != transMap.end()) ? transMap.at(target) : getTrans(target, iterTypo);

		// insertCost = getIns(target,iterTypo);
		// delCost = getDel(target, iterTypo, numOfCalls);
		// subCost = getSub(target, iterTypo);
		// transCost = getTrans(target, iterTypo);

	//If insert cost is the minumum
    if(insertCost<= delCost && insertCost <= subCost && insertCost<=transCost){
		lowestCost=insertCost;
		iterTypo++;
		numOfCalls++;

	    output << " Insert " << typo[iterTypo-1]<<" at "<<iterTypo-1 << endl;
	    target=typo[iterTypo]+target;

	//If delete cost is the minumum
    }else if (delCost<= insertCost && delCost <= subCost && delCost<=transCost){

		lowestCost=delCost;
		iterTypo++;
		numOfCalls++;
		
		output << " Delete " << iterTypo-1 << endl;
		
	//If substitute cost is the minumum	
	}else if (subCost<= delCost && subCost <= insertCost && subCost<=transCost){

		lowestCost=subCost;
		iterTypo++;
		numOfCalls++;
		
		output << " Substitute " << typo[iterTypo-1] << " at " <<iterTypo-1<< endl;
		target[0]=typo[iterTypo];

	//If transpose cost is the minumum
    }else if (transCost<= delCost && transCost <= insertCost && transCost<=subCost){

		lowestCost=transCost;
		iterTypo+=2;
		snip=2;
		numOfCalls++;
		
		output << " Transpose " << iterTypo-2<<"-"<<iterTypo-1<< endl;
		swap(target[0], target[1]);
    }

  }

	if(target[0]==typo[iterTypo]){
		iterTypo++;
		numOfCalls++; 
	}

  return lowestCost+typoCost(output, target.substr(snip, target.size()), iterTypo);
}

//***************************************************************************
// getIns - gets the cost to insert based on the condition
//***************************************************************************
int getIns(string target, int iterTypo){
	int thisCost;

	Key ins=getKey(typo[iterTypo]);         	//Character
	Key charBefore=getKey(typo[iterTypo-1]);	//Character before
	Key charAfter=getKey(typo[iterTypo+1]);		//Character after

	if(typo[iterTypo+1]==target[0]){
	  if (ins.ch == '\0' || target[0] == '\0'){
	    return 99;
	  }else if(charBefore.ch == ins.ch){   						//Repeated Character
	    return 1;
	  }else if(charBefore.row == 3 && ins.ch == ' ') { 			//Space after key in bottom row
	    return 2;
	  }else if(charBefore.row < 3 && ins.ch == ' '){ 			//Space after something else
	    return 6;
	  }else if(charBefore.ch == ' ' || charAfter.ch == ' '){ 	//Char before or after space
	    return 6;
	  }else if(charBefore.isRight == ins.isRight){				//Before another key on same hand
	    return keyDistance(charBefore,ins);
	  }else if(charAfter.isRight == ins.isRight){ 				//after another key on same hand
	    return keyDistance(charAfter,ins);
	  }else{													//before or after a key on opposite hand
	    return 5;
	  }
	}else{
		return 99;
	}
}

//***************************************************************************
// getDel - gets the cost to delete based on the condition
//***************************************************************************
int getDel(string target, int iterTypo, int numOfCalls){

  Key del=getKey(target[0]);         //character which needs to be deleted
  Key typoBefore=getKey(typo[iterTypo-1]);
  Key tarAfter=getKey(target[1]);

  if(typo[iterTypo+1] == target[0]){ 						//will check if deletion is possible
		if(target[0]== typo[iterTypo+1] && typo[iterTypo]== target[1]){ //dont delete because its trans
			delMap[target]=99;
			return 99;
		}else if(target[0]==target[1]){						//Repeated Character
      delMap[target]=1;
      return 1;
    }else if(target[0]==' '){ 								//Space
      delMap[target]=3;
      return 3;
    }else if(del.isRight == tarAfter.isRight){ 				//char after another key on same hand
      delMap[target]=2;
      return 2;
    }else if(numOfCalls==0){ 								//First character
      delMap[target]=6;
      return 6;
    }else{  												//char after space or key on diff hand
      delMap[target]=6;
      return 6;
    }
  }
  delMap[target]=99;
  return 99; 												// deletion is not possible and return a ridicolously large number
}

//***************************************************************************
// getSub - gets the cost to substitute based on the condition
//***************************************************************************
int getSub(string target, int iterTypo){

  Key subTypo=getKey(typo[iterTypo]);
  Key subTar=getKey(target[0]);

	if(typo[iterTypo+1]==target[0]){ 						//Substitution is not possible, looks like deletion
		subMap[target]=99;
		return 99;
	}else if(target[0] == ' ' || subTypo.ch == ' '){		//Space for anything or anything for space
    subMap[target]=6;
	return 6;
  }else if(subTar.isRight == subTypo.isRight){				//Key for another on same hand
	   subMap[target]=keyDistance(subTypo,subTar);
	return keyDistance(subTypo,subTar);
  }else if(subTar.finger == subTypo.finger){				//Key for another on same finger
	   subMap[target]=1;
	return 1;
  }else{													//Key for another on different finger, other hand
	   subMap[target]=5;
	return 5;
  }

}

//***************************************************************************
// getTrans - gets the cost to transpose based on the condition
//***************************************************************************
int getTrans(string target, int iterTypo){
  Key curTarget=getKey(target[0]);
  Key nextTarget=getKey(target[1]);
  Key curTypo=getKey(typo[iterTypo]);
  Key nextTypo=getKey(typo[iterTypo+1]);


  if(target[0]== typo[iterTypo+1] && typo[iterTypo]== target[1]){
    if(curTarget.ch ==' ' || nextTarget.ch == ' '){ 		// Space with anything

      transMap[target]=3;
      return 3;
    }else if(curTarget.isRight != nextTarget.isRight){ 		// Keys on different hand
      transMap[target]=1;
      return 1;
    }else{
      transMap[target]=2; 									// Keys on same hand
      return 2;
    }
  }

  transMap[target]=99;
  return 99;												//Transpose is not possible and return a ridicolously large number
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
