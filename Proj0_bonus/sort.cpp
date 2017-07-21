#include <iostream>
#include "sort.h"

using namespace std;

void CompetencyHeap(Subject *sub, int i, int max);
void BuildCompHeap(Subject *, int n);

//Builds the heap using CompetencyHeap
// sub	- subject in question
// n	- total number of subjects
void BuildCompHeap(Subject *sub, int n){
    for (int i = n -1; i >= 0; --i){
        CompetencyHeap(sub, i, n);
    }
}

//Required function - repeatedly heapifies the subject array
// sub	- subject in question
// n	- total number of subjects
void dksort(Subject *sub, int n)
{
    BuildCompHeap(sub, n);
	
    for (int i = n - 1; i > 0; --i) 
	{
        swap(sub[0], sub[i]);
        CompetencyHeap(sub, 0, i);
    }
}

// Heapify-esque function
// sub	- subject in question
// i	- current largest
// max	- max value
void CompetencyHeap(Subject *sub, int i, int max)
{
    int largest = i; 	//Largest value
    int l = 2 * i + 1;	//Left branch
    int r = 2 * i + 2;	//Right branch

    if (l < max and sub[l] > sub[i])	//
	{
        largest = l;
    }
	
    if (r < max and sub[r] > sub[largest])
	{
        largest = r;
    }
	
    if (largest != i)
	{
        swap(sub[i], sub[largest]);
        CompetencyHeap(sub, largest, max);
    }
}
