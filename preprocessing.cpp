//
//  preprocessing.cpp
//  swapathon
//
//  Created by Matthew Lane on 11/27/16.
//  Copyright © 2016 Matthew Lane. All rights reserved.
//

#include "preprocessing.hpp"


// *************************************************************************
// This function opens the file and counts the number of children and gifts.
// *************************************************************************

void getGiftAndChildrenCount(string filename, int &childCount, int &giftCount){
    
    ifstream inputFile;
    string input;
    
    inputFile.open(filename);
    
    if (!inputFile.is_open()) {
        cout << "ERROR! File unopened";
        exit(1);
    }
    
    // Get the number of gifts!
    getline(inputFile, input);
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '\t'){
            giftCount += 1;
        }
    }
    // for additional tab after child prior to num
    giftCount -= 1;
    cout << "gift count == " << giftCount << endl;
    
    // work with first child:
    while(getline(inputFile, input)){
        childCount += 1;
    }
    cout << "children count = " << childCount << endl;
    inputFile.close();
    
    
}


// ***************************************************************************
// This function copies in the data for each child into a corresponding struct
// ***************************************************************************

Child* getChildrenArray(string filename, int childCount, int giftCount){
    struct Child children[childCount];
    ifstream inputFile;
    string input;
    inputFile.open(filename);
    
    // get over the first line: (make sure all is hunky dory)
    getline(inputFile, input);
    cout << input << endl;
    
    
    
    // NOW WORK WITH CHILDREN:
    vector<string> items;
    for (int i = 0; i < childCount; i++) {
        getline(inputFile, input);
        
        // Remove the return value
        input.erase(input.end() - 1);
        
        items = split(input, '\t');
        
        children[i].numCopies = atoi(items[1].c_str());
        
        
        // create a new array of data!
        
        children[i].giftRank = new int[giftCount];
        
        for (int j = 0; j < giftCount; j ++){
            children[i].giftRank[j] = atoi(items[2+j].c_str());
            
        }
    }
    
    inputFile.close();
    return children;
}




// *************************************************************************
// This function creates a matrix from the Children structs and unpacks the
// data so that each gift has its own corresponding row.
// *************************************************************************
int** createMatrix_Rank(Child *children, int childrenCount, int giftCount, int matrixHeight){
    int** matrix = 0;
    int child = 0;
    int turnsToNextChild = 100000;
    
    matrix = new int*[matrixHeight];
    
    
    turnsToNextChild = children[0].numCopies;
    for (int i = 0; i < matrixHeight; i++) {
        matrix[i] = new int[giftCount];
        
        
        for (int j = 0; j < giftCount; j++) {
            int num = children[child].giftRank[j];
            matrix[i][j] = num;
        }
    
        if (turnsToNextChild == 1) {
            child++;
            turnsToNextChild = children[child].numCopies;
            continue;
        }
        turnsToNextChild --;
    }
    
    return matrix;
}


// *************************************************************************
// This function creates a O1 gifting matrix that is used as the incumbent
// *************************************************************************

int** createMatrix_Gifting01(int height, int width){
    int** matrix = 0;
    matrix = new int*[height];
    
    for (int i = 0; i < height; i++) {
        matrix[i] = new int[width];
        
        for (int j = 0; j < width; j++) {
            matrix[i][j] = 0;
        }
    }
    
    return matrix;
}




// ****************************************************************************************
// This functions changes the weights of the ranking matrix to an arbitrarily high number
// ****************************************************************************************

void addMatrixRankConstraint(int**matrix, int height, int width){
    double upperBound = 0.75 * width;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] > upperBound ) {
                matrix[i][j] = 100 * width;
            }
        }
    }

}



// *************************************************************************
// This function returns the height of the ranking matrix
// *************************************************************************

int getMatrixHeight(Child *children, int childrenCount){
    int matrixSize = 0;
    
    for (int i = 0; i < childrenCount; i++) {
        matrixSize += children[i].numCopies;
    }

    return matrixSize;
    
}



// *************************************************************************
// This function prints the data from the child struct array
// *************************************************************************

void printChildData(Child *children, int childrenCount, int giftCount){
    
    for (int i = 0; i < childrenCount; i++) {
        cout << children[i].numCopies;
        
        for (int j = 0; j < giftCount; j++) {
            cout << " "<< children[i].giftRank[j];
        }
        
        cout << endl;
    }

}






// *************************************************************************
// This function prints the matrix data of a given height and width (INT)
// *************************************************************************

void printMatrix(int** matrix, int height, int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << setw(5) <<  matrix[i][j] << " ";
        }
        cout << endl;
    }
}


// *************************************************************************
// This function prints the matrix data of a given height and width (DOUBLE)
// *************************************************************************

void printMatrix(double** matrix, int height, int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << setw(5) << setprecision(2) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// *************************************************************************
// This function delets the matrix data of a given height and width (INT)
// *************************************************************************

void deleteMatrixData(int **matrix, int height){
    for (int h = 0; h < height; h++)
    {
        delete [] matrix[h];
    }
    delete [] matrix;
}


// *************************************************************************
// This function deletes the matrix data of a given height and width (DOUBLE)
// *************************************************************************

void deleteMatrixData(double **matrix, int height){
    for (int h = 0; h < height; h++)
    {
        delete [] matrix[h];
    }
    delete [] matrix;
}




// *************************************************************************
// These functions split the string data for the child struct vectors
// Functions were taken from stack overflow:
// http://stackoverflow.com/questions/236129/split-a-string-in-c
// *************************************************************************


void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


