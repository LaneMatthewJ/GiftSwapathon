//
//  swapathon.cpp
//  swapathon
//
//  Created by Matthew Lane on 11/27/16.
//  Copyright © 2016 Matthew Lane. All rights reserved.
//

#include "swapathon.hpp"

int **rankMatrix = 0;
int **incumbentSolution = 0;
int incumbentFitness = 1000000;

void printToFile(){
    ofstream file;
    
    
}


// ****************************************************************************
// This function relaxes the 01 gifting constraint for the matrix passed into it
// ****************************************************************************
double** getRelaxedMatrix_ChoiceMatrix(int **rankMatrix, int height, int width){
    
    double **relaxedMatrix = 0;
    int minimalElement = 0;
    
    relaxedMatrix = new double*[height];
    
    
    // get the minimal element per row:
    for (int i = 0; i < height; i++) {
        relaxedMatrix[i] = new double[width];
        
        for (int j = 0; j < width; j++) {
            relaxedMatrix[i][j] = 0;
        }
        
        minimalElement = getMinimalElement(rankMatrix[i], width);
        
        relaxedMatrix[i][minimalElement] = 1.0;
        
    }
    
    return relaxedMatrix;
}


// ****************************************************************************
// This function gets the minimal elements within the gifting matrix.
// ****************************************************************************

int getMinimalElement(int *matrixRow, int rowSize){
    
    int elementNumber = 0;
    int previousWeight = 100000;
    
    
    for (int i = 0; i < rowSize; i++) {
        if (matrixRow[i] < previousWeight) {
            previousWeight = matrixRow[i];
            elementNumber = i;
        }
    }
    
    return elementNumber;
}

// ****************************************************************************
// This function updates the weights!
// ****************************************************************************

void updateWeightsFromMultipleChoices_RelaxedMatrix(double** relaxedMatrix, int height, int width){
    
    // calculate the amount to divide the values in that by!
    double divisor;
    for (int j = 0; j < width; j++) {
        
        divisor = 0;
        for (int i = 0; i < height; i++) {
            divisor += relaxedMatrix[i][j];
        }
        
        if (divisor <= 0) {
            continue;
        }
        
        for (int i = 0; i < height; i++) {
            relaxedMatrix[i][j] = relaxedMatrix[i][j] / divisor;
        }
    }
}

// ****************************************************************************
// This function finds the column with the smallest weights to split on
// ****************************************************************************


int getColumnToSplitOn(double **relaxedMatrix, int height, int width){
    
    int element = -1;
    double lowestNumber = 100000;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (relaxedMatrix[i][j] > 0 && relaxedMatrix[i][j] < lowestNumber) {
                lowestNumber = relaxedMatrix[i][j];
                element = j; // splitting on the gifts.
            }
        }
    }
    return element;
}


// ****************************************************************************
// This function finds gets the numbers for the gifts to split on
// ****************************************************************************

int *getRowsThatSplit(double **relaxedMatrix, int height, int splittingColumn){
    
    int *splittingRows = new int[height];
    
    for (int i = 0; i < height; i++) {
        if (relaxedMatrix[i][splittingColumn] != 0){
            splittingRows[i] = 1;
        } else {
            splittingRows[i] = 0;
        }
    }
    
    return splittingRows;
}

// ****************************************************************************
// This creates a new ranking matrix for the new node
// ****************************************************************************

int **createNewRankingMatrix(int **oldRankingMatrix, int height, int width, int split_row, int split_column){
    int **newRankingMatrix = 0;
    newRankingMatrix = new int*[height];
    
    
    for (int i = 0; i < height; i++) {
        newRankingMatrix[i] = new int[width];
        for (int j = 0; j < width; j++) {
            newRankingMatrix[i][j] = oldRankingMatrix[i][j];
        }
    }
    
    
    for (int i = 0; i < height; i++) {
        if (i == split_row) {
            newRankingMatrix[i][split_column] = 1;
        } else {
            newRankingMatrix[i][split_column] = 100*width + 1;
        }
    }
    
    return newRankingMatrix;
}


// ****************************************************************************
// This checks to see if the matrix is integral!
// ****************************************************************************

bool isIntegralMatrix(double **choiceMatrix_Relaxed, int height, int width){
    bool isIntegral = true;
    
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (choiceMatrix_Relaxed[i][j] != 0 && choiceMatrix_Relaxed[i][j] != 1) {
                isIntegral = false;
                return isIntegral;
            }
        }
    }
    
    return isIntegral;
}

// ****************************************************************************
// This funciton updates the incumbent
// ****************************************************************************


void updateIncumbentSolution(double** choiceMatrix_Integral, int height, int width){
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            incumbentSolution[i][j] = static_cast<int>(choiceMatrix_Integral[i][j]);
        }
    }
    
    
    
}

// ****************************************************************************
// This function calculates the fitness for each matrix (INT)
// ****************************************************************************


int calculateFitness(int **rankMatrix, int **choiceMatrix, int height, int width){
    int fitnessValue = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fitnessValue += rankMatrix[i][j] * choiceMatrix[i][j];
        }
    }
    return fitnessValue;
}

// ****************************************************************************
// This function calculates the fitness for each matrix (DOUBLE)
// ****************************************************************************


int calculateFitness(int **rankMatrix, double **choiceMatrix, int height, int width){
    double fitnessValue = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fitnessValue += rankMatrix[i][j] * choiceMatrix[i][j];
        }
    }
    return static_cast<int>(fitnessValue);
}


// ****************************************************************************
// This is the swapathon! Generates new nodes, relaxes, and switches!
// ****************************************************************************

void swapathon(int **rankingMatrix, int height, int width){
    
    
    double **relaxedMatrix = getRelaxedMatrix_ChoiceMatrix(rankingMatrix, height, width);
    updateWeightsFromMultipleChoices_RelaxedMatrix(relaxedMatrix, height, width);
    int splittingColumn = getColumnToSplitOn(relaxedMatrix, height, width);
    int *rows = getRowsThatSplit(relaxedMatrix, height, splittingColumn);
    
    
    //*********************************
    //          CHECK FOR FITNESS!
    // ********************************
    
    int currentFitness = 1000001;
    currentFitness = calculateFitness(rankMatrix, relaxedMatrix, height, width);
    if (currentFitness > incumbentFitness) {
        return;
    }
    
    
    
    //*********************************
    //          CHECK FOR INTEGRALITY!
    // *******************************
    
    bool isIntegral = isIntegralMatrix(relaxedMatrix, height, width);
    if (isIntegral) {
        
        
        updateIncumbentSolution(relaxedMatrix, height, width);
        incumbentFitness = calculateFitness(rankMatrix, incumbentSolution, height, width);
        
        // Delete matrix data to prevent memory leakage
        deleteMatrixData(relaxedMatrix, height);
    
        return;
    }
    
    
    
    //*********************************
    //          DOWN THE RABBIT HOLE!
    // *******************************
    for (int i = 0; i < height; i++){
        if (rows[i] == 1) {
            int** newRankingMatrix = createNewRankingMatrix(rankingMatrix, height, width, i, splittingColumn);
            
            swapathon(newRankingMatrix,  height, width);
            
            deleteMatrixData(newRankingMatrix, height);
        }
    }
    
    deleteMatrixData(relaxedMatrix, height);
    delete [] rows;
}



//******************************************
//          THIS FUNCTION PRINTS TO THE FILE!
// *****************************************
void printSwapsToFile(Child *children, int childrenCount, int giftCount, string filename){
    
    FILE * pFile;
 //   string ofilename = filename.substr(0, filename.size() - 4) + "_output.txt"; 

	
    pFile = fopen ("output_file.txt" , "w"); 

    if (pFile==NULL)
    {
        cout << "FAILURE!\n";
        exit(0);
    }
    
    
    
    
    cout << "All Scores=" << incumbentFitness << endl;
    fprintf(pFile, "All Scores=%d\n", incumbentFitness);
    
    
    cout << "Child\t" << "num\t";
    fprintf(pFile, "Child\tnum\t ");
    
    for (int j = 0; j < giftCount; j++) {
        
        cout << "g" << j+1 << "\t";
        fprintf(pFile, "g%d\t", j+1);
    }
    
    cout << "\n";
    fprintf(pFile, "\n");
    
    int giftOutput[giftCount];
    
    for (int child = 0; child < childrenCount; child++) {
        cout << "C" << child << "\t" << children[child].numCopies << "\t";
        
        fprintf(pFile, "C%d\t%d\t",child, children[child].numCopies);
        
        for (int x = 0; x < children[child].numCopies; x++) {
            
            
            for (int i = 0; i < giftCount; i++) {
                giftOutput[i] = 0;
            }
            
            
            int indexer = 0;
            
            if (child != 0) {
                for (int i = 0; i < child; i++) {
                    indexer += children[i].numCopies;
                }
                
            }
            
            
            int bound = children[child].numCopies + indexer;
            
            for (int i = indexer; i < bound; i++) {
                for (int j = 0; j < giftCount; j++) {
                    if (incumbentSolution[i][j] == 1) {
                        giftOutput[j] = rankMatrix[i][j];
                    }
                }
            }
            
            
        }
        for (int i = 0; i < giftCount; i++) {
            cout << giftOutput[i] << "\t";
            
            fprintf(pFile, "%d\t", giftOutput[i]);
            
        }
        cout << endl;
        fprintf(pFile, "\n");
        
    }
    
    fclose(pFile);
    
    
}

