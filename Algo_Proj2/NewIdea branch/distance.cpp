#include <iostream>
#include "distance.h"
using namespace std;

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

int keyDistance(Key k1, Key k2)
{
    int rowDist = k2.row - k1.row;
    int colDist= k2.col - k1.col;

	rowDist = (rowDist >= 0) ? rowDist : (rowDist * -1);
	colDist = (colDist >= 0) ? colDist : (colDist * -1);

	return (rowDist > colDist) ? rowDist : colDist;
  }