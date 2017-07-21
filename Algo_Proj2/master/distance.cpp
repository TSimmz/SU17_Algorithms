#include <iostream>
#include "typo.h"
#include "distance.h"
using namespace std;

void getKey(Key *k)
{
  char chars[39] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
					         'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
  					       'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
					         'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'};

  for(int i=0; i<40; i++)
	{
  		if(chars[i] == k->ch){
          //Defining row
          k.row = i/10;
          //Defining col
          k.col = i%10;
  		}
    //Setting hand
		isRight = (k->col >4) ? true : false;
    //Setting finger
    if(k.col>2 && k.col <7){
      k.finger=0;
    }else if (k.col==2 !! k.col==7) {
      k.finger=1;
    }else if (k.col==1 !! k.col==8){
      k.finger=2;
    }else if (k.col==0 !! k.col==9){
      k.finger=1;
    }

  	}
}

int keyDistance(Key k1, Key k2)
{

  //  std::cout << k1.ch << k1.row << k1.col <<'\n';
  //  std::cout << k2.ch << '\n';



    int rowDist= k2.row - k1.row;
    int colDist= k2.col - k1.col;

    std::cout << rowDist << '\n';
    std::cout << colDist << '\n';

    if( rowDist > colDist){
      return rowDist;
    } else{
      return colDist;
    }
  	// 1234567890
  	// qwertyuiop
  	// asdfghjkl;
  	// zxcvbnm,.
  }

// int main(){
  // Key q,f;
  // q.ch='q';
  // f.ch='f';
  // getKey(&q);
  // getKey(&f);
  // int distance = dist(q,f);
  // std::cout << "Distance is: " << distance <<endl;
  // return 0;
// }
