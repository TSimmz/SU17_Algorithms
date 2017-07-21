#ifndef _DISTANCE_H
#define _DISTANCE_H

#define KROW 4
#define KCOL 10

//Structure to define each key.
typedef struct key{  
	char ch;
	int row;
	int col;
	bool isRight; 	//True if character is right hand
	int finger;		//1 if index, 2 if mi**le, 3 is ring, 4 is pinky. 
} Key;

Key keyboard[KROW][KCOL];

void setKey();
Key getKey(char);
int keyDistance(Key k1, Key k2);

#endif