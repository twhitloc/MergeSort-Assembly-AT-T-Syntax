//
//  Header.h
//  ArchitectureProject
//
//  Created by Tyler Whitlock on 4/15/15.
//  Copyright (c) 2015 Tyler Whitlock. All rights reserved.
//

#ifndef _HEADER_h
#define _HEADER_h



#include <stdio.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


int getArraysize();                                                     // Get the array Size 1M - 50M

template<class T>
void merge(T list[], int lowerBound, int middle, int upperBound);      //C++ merge sort template

template<class T>
void mergeSort(T list[], int lowerBound, int upperBound);              //C++ merge sort template


void displayArray(int *list, int arraySize);                                //Display the array *not currently used, but for convenience and checking
void displayEnd(int arraySize, float cmerge, float rsort, float assembly);  //Display findings
void makeRandom(int list[], int arraySize);                                 //Randomization
void programDescription();                                                  //Show the user the description of the program
void RadixSortLSD(int *a, int arraySize);                                   //C++ LSD Radix Sort


/*
*       FUNCTIONS
*/

                                        /*Describe program to user*/

void programDescription(){
    cout << "This program will use C++ and Assembly to merge sort a large array\n\n";
    cout << "This sort will be done first in pure C++, and then in Assembly\n\n";
    cout << "The times of both sorts will be output to the user after the randomized array has been sorted\n\n\n";
    return;
}




                                    /*Get the array size via user input*/

int getArraysize(){
    int arraySize =0;
    
    if(arraySize >=51 || arraySize < 1 )
    {
        do
        {
            arraySize =0;
            stringstream sstr;
            string textline = "";
            cout << "Please enter a size for your array in millions, such that 1 <= n <= 50\n:";
            getline(cin, textline);
            
            sstr << textline;
            sstr >> arraySize;
            
            
        } while((arraySize >=51 || arraySize < 1));
        
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    return arraySize;
}



                            /*Displays the array taking the list and list's size as parameters*/

void displayArray(int *list, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        cout << setw(5)<< list[i]<< "  ";
        if (i %10 ==0)
            cout << endl;
    }
    cout << "\n\n";
    return;
}




                            /* Display findings, takes list size, and times (floats) */

void displayEnd(int arraySize, float cmerge, float rsort, float assembly)
{
    
    cout << setw(60) << "The C++ function to merge sort this array of " << arraySize/1000000 <<
    " Million numbers took :   " << cmerge  << " seconds\n";
    cout << setw(60) << "The C++ Radix sort to sort the array of " << arraySize/1000000 <<
    " Million numbers took :   " << rsort << " seconds\n\n";
    cout << setw(60)  << "The Assembly function to merge sort this array of " << arraySize/1000000 <<
    " Million numbers took :   " << assembly << " seconds\n\n";
    
    cout << "       The sort using x86 required :  " << ((assembly/cmerge)*100) << "% of the time that the C++ function required\n";
    cout << "       The radix sort required     :  " << ((rsort/cmerge)*100) << "% of the time that the C++ merge sort required\n";
    cout << "       The radix sort required     :  " << ((rsort/assembly)*100) << "% of the time that the x86 merge sort required\n\n";
    
}


/* Randomize the list's values taking in a list and its size */

void makeRandom(int list[], int arraySize)
{
    for(int i = 0; i < arraySize; i++)
        list[i] = rand() %  10000000 + 0;
    return;
}




                            /* Merging Sort, takes list/pointer to list, lower limit index, middle index and upper limit index */

template<class T>
void merge(T list[], int lowerBound, int middle, int upperBound)
{
    // Variables declaration.
    int * b = new int[upperBound + 1 - lowerBound];
    int h, i, j, k;
    h = lowerBound;
    i = 0;
    j = middle + 1;
    // Merges the two array's into b[] until the first one is finished
    while ((h <= middle) && (j <= upperBound))
    {                                                           //if lower bound is <= middle and middle+1 is <= upper continue
        if (list[h] <= list[j])
        {                                                       //if lower index is lower value then place into temp array
            b[i] = list[h];
            h++;
        }
        else
        {
            b[i] = list[j];                                     //otherwise place the other element into temp array
            j++;
        }
        i++;
    }
    if (h>middle)
    {                                                           //if lowerbound is greater than the middle of the array
        for (k = j; k <= upperBound; k++)                       //k = middle+1
        {                                                       //then place each element into temp array
            b[i] = list[k];
            i++;
        }
    }
    else
    {
        for (k = h; k <= middle; k++)                           //otherwise k = lowerbound of partition
        {
            b[i] = list[k];                                     //then place every element into temp array
            i++;
        }
    }
    for (k = 0; k <= upperBound - lowerBound; k++)              //then put the list back together using the temp array
    {
        list[k + lowerBound] = b[k];
    }
    
    delete[] b;
    b = NULL;
}




                                    /* Merge sort recursively taking the list, lower bound and upper bound */

template<class T>
void mergeSort(T list[], int lowerBound, int upperBound)
{
    int middle;
    if (lowerBound<upperBound)                                  //if the list isn't empty or a single item then sort it
    {
        middle = (lowerBound + upperBound) / 2;
        mergeSort(list, lowerBound, middle);
        mergeSort(list, middle + 1, upperBound);
        merge(list, lowerBound, middle, upperBound);
    }
}





                                    /* Perform the least significant digit radix sort, taking in pointer to array and array Size */

void RadixSortLSD(int *a, int arraySize)
{
    if( a == NULL | arraySize == 0 )
        return;
    
    int i;
    int *bucket = new int[arraySize];
    int maxVal = 0;
    int digitPosition = 1;
    for ( i = 0; i < arraySize; i++)
    {
        if ( a[i] > maxVal )                        // get the largest value in the array (will need for digits)
            maxVal = a[i];
    }
    
    while ( maxVal / digitPosition > 0 )
    {                                                       // loop for the number of digits in maxVal
        
                                                            // To keep the order, start from back side
        for(i = arraySize - 1; i >= 0; i--)
            bucket[  a[i] / digitPosition % 10 ] = a[i];    // put elements into buckets
                                                            // rearrange the original array using elements in the bucket
        for(i = 0; i < arraySize; i++)
            a[i] = bucket[i];
                                                            // move up by one digit
        digitPosition *= 10;
    }
    
    delete bucket;
    bucket = NULL;
}


#endif