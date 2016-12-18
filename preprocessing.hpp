//
//  preprocessing.hpp
//  swapathon
//
//  Created by Matthew Lane on 11/27/16.
//  Copyright © 2016 Matthew Lane. All rights reserved.
//

#ifndef preprocessing_hpp
#define preprocessing_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;



struct Child{
    int numCopies; // for the number of gifts
    int *giftRank; 
};


// preprocessing functions

void getGiftAndChildrenCount(string, int &, int &);
Child* getChildrenArray(string, int, int);
int** createMatrix_Rank(Child*, int, int, int);
int** createMatrix_Gifting01(int, int);
void addMatrixRankConstraint(int**, int, int);

int getMatrixHeight(Child*, int);
void printChildData(Child*, int, int);
void printMatrix(int** , int , int );
void printMatrix(double**, int, int);
void deleteMatrixData(int**, int);
void deleteMatrixData(double**, int);



//vector split functions were obtained from stack overflow
void split(const string &, char, vector<string> &);
vector<string> split(const string &, char);




#endif /* preprocessing_hpp */
