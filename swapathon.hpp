//
//  swapathon.hpp
//  swapathon
//
//  Created by Matthew Lane on 11/27/16.
//  Copyright © 2016 Matthew Lane. All rights reserved.
//

#ifndef swapathon_hpp
#define swapathon_hpp

#include <stdio.h>
#include "preprocessing.hpp"


extern int **rankMatrix;
extern int **incumbentSolution;
extern int incumbentFitness;



// get the relaxed matrix for the node:
double** getRelaxedMatrix_ChoiceMatrix(int **, int, int);
int getMinimalElement(int *, int);

void updateWeightsFromMultipleChoices_RelaxedMatrix(double** , int , int );
int getColumnToSplitOn(double **, int, int);
int *getRowsThatSplit(double **, int , int);
bool isIntegralMatrix(double **, int, int);


void swapathon(int **, int , int );
void printSwapsToFile(Child *, int , int, string);





#endif /* swapathon_hpp */
