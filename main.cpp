//
//  main.cpp
//  ArchitectureProject
//
//  Created by Tyler Whitlock on 4/9/15.
//  Copyright (c) 2015 Tyler Whitlock. All rights reserved.
//
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include "Header.h"
#include <iterator>
#include <algorithm>
using namespace std;

//The assembly function to sort
extern "C" int* asmMain( int a, int b[]);








//Get array and randomize it
//sort it/time it
int main() {
    
    srand(time(NULL));
    int arraySize =0;
    clock_t t;
    
    programDescription();
    arraySize = getArraysize() * 1000000;           //comment this line if you wish to test output
    
    
    t = clock();                                    //set up our timer
    int *list = new int[arraySize];                 //create out blank array
    t = clock() - t;
   
    cout << setw(45)<< "Insatiating the array for this problem took:"<< setw(10)<< ((float)t)/CLOCKS_PER_SEC << "  Seconds " << endl;
    
    t = clock();
    makeRandom(list, arraySize);                    //fill up array with random values
    t = clock() - t;
    
    cout << setw(45) <<"Creating the values for this array took:" << setw(10)<<((float)t)/CLOCKS_PER_SEC << "  Seconds";
    
    
    //displayArray(list, arraySize);         //Uncomment this if you wish to see that it is sorted.
    //Set the arraySize variable manually and comment out the user input function if you wish to do so.
    
    cout << "\n...C++ Sorting...\n\n";            //Let the user know we are working, since we have a large data set. Wont be long now.
    t = clock();
    mergeSort(list, 0,arraySize);                 // Call the C++ merge sort function and time it
    t = clock() -t;
    float cmerge = (((float)t)/CLOCKS_PER_SEC);
    makeRandom(list, arraySize);
    
    
    
    cout << "\n...Radix Sorting...\n\n";
    t = clock();
    RadixSortLSD(&list[0],arraySize);
    t = clock() -t ;
    float rsort = (((float)t)/CLOCKS_PER_SEC);
    //displayArray(list, arraySize);
    makeRandom(list, arraySize);
    
    
    
    cout << "\n...Assembly Sorting...\n\n";
    t = clock();
    list = asmMain(arraySize, list);       // Call the assembly merge sort function and time it
    t = clock() -t;
    
    
   
    float assembly = (((float)t)/CLOCKS_PER_SEC);
    displayEnd(arraySize, cmerge, rsort, assembly);
    
    delete list;
    list = NULL;
    return 0;
}
