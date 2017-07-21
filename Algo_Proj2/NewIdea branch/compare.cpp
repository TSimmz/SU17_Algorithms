//
//  compare.cpp
//
//
//  Created by Steven Nguyen on 7/11/17.
//
//

#include <stdio.h>
#include "typo.h"
#include "distance.h"

int string_compare( string target, string typo)
{

    Cell targetValues[strlen(target)+1]; 	//A cell of target costs
    char typoArray[strlen(typo)]; 			//an array of Typo string
    char targetArray[strlen(target)+1]; 	//an array of Target string
    /*
    *  i is counter for Target String
    *  j is counter for Typo String
    *  k is type of typo. (Inserting, Deleting, Substituting, Transposing)
    */
    int i,j,k;              /* counters */
    int opt[4];             /* cost of the four typo types */

    /*for (i=0; i<MAXLEN; i++)
    {
        row_init(i);
        column_init(i);
    }*/

    for (i=1; i<strlen(s); i++)
    {
        while (target.at(i) != typo.at(i)) //making sure that they arent same
        {

            ￼opt[INSERT] = insert(target[i],target[i-1]);
            //opt[DELETE] = m[i][j-1].cost + del(s[i]);
            //opt[SUB] = m[i-1][j].cost + sub(s[i]);
            //opt[TRAN] = m[i-1][j].cost + tran(s[i],t[j]);

            m[i][j].cost = opt[INSERT];
            m[i][j].parent = INSERT;

            for (k=DELETE; k<=TRAN; k++)
            {
                if (opt[k] < m[i][j].cost)
                {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
            }
        }
    }

}

//needs edits (a lot)
insert(char a, char b)
{
    if(a == b)
        return 1;
    if((b.row == 4) && (a == ' '))
        return 2;
    if((b.row != 4) && (a == ' '))
        return 6;
    if(((b != ' ') && (a == ' ')) || ((b == ' ') && (a != ' ')))
        return 6;



}
