//
//  main.cpp
//  swapathon
//
//  Created by Matthew Lane on 11/26/16.
//  Copyright © 2016 Matthew Lane. All rights reserved.
//

#include "swapathon.hpp"


int main() {
    
    int giftCount = 0;
    int childrenCount = 0;
    int rankingMatrixHeight = 0;
    int menuChoice = 0;     
    string input;
    ifstream inputFile;
    string filename;
    
    Child *children;
    cout << "Please make a choice: \n"; 
    cout << "1. 4 Children 10 gifts\n2. 4 Children 11 gifts\n3. 4 Children 12 gifts\n4. 4 Children 13 gifts\n5. Enter your own file name for import. ";

    cin >> menuChoice; 
 
    if(menuChoice == 1){
 	filename = "ex_4child_10gift.txt"; 
    } else if (menuChoice == 2) {
	filename = "ex_4child_11gift.txt"; 
    } else if (menuChoice == 3){
	filename = "ex_4child_12gift.txt";
    } else if (menuChoice == 4){
	filename = "ex_4child_13gift.txt"; 
    } else if (menuChoice == 5){
	cout << "Please enter the filename: "; 
	cin >> filename; 
    } 
    else {
 	cout << "Not a valid choice, default run:\n4 Children 10 gifts\n"; 
    
	filename = "ex_4child_10gift.txt"; 
    }
     
    
    //******************************************************************
    //******************************************************************
    
    
    // ** Preprocessing **
    getGiftAndChildrenCount(filename, childrenCount, giftCount);
    children = getChildrenArray(filename, childrenCount, giftCount);
    printChildData(children, childrenCount, giftCount);
    
    // ** Rank Matrix Generation **
    rankingMatrixHeight = getMatrixHeight(children, childrenCount);
    rankMatrix = createMatrix_Rank(children, childrenCount, giftCount, rankingMatrixHeight);
    printMatrix(rankMatrix, rankingMatrixHeight, giftCount);
    addMatrixRankConstraint(rankMatrix, rankingMatrixHeight, giftCount);
    
    // ** Gifting Matrix Generation **
    incumbentSolution = createMatrix_Gifting01(rankingMatrixHeight, giftCount);
    printMatrix(incumbentSolution, rankingMatrixHeight, giftCount);
    
    
    
    //******************************************************************
    //******************************************************************
    
    
    
    
    // ** Do the swapathon!! **  
    swapathon(rankMatrix, rankingMatrixHeight, giftCount);
    
    

    //*****************************************************************
    //****************************************************************

    cout << "Incumbent solution: \n";
    printMatrix(incumbentSolution, rankingMatrixHeight, giftCount);
    cout << "Fitness: " << incumbentFitness << endl;
    
    //******************************************************************
    //******************************************************************
    
    printSwapsToFile(children, childrenCount, giftCount, filename);
       
    
    // clean up memory!
    deleteMatrixData(rankMatrix, rankingMatrixHeight);
    deleteMatrixData(incumbentSolution, rankingMatrixHeight);
    
    
    return 0;
}


