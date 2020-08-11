#include <stdio.h>
#include<fstream>
#include<iostream>

//**************************Creating 2d array*********************************************
int **matrix(int *arr, int row, int col) {
    int index = 0;  //I borrowed Prof Alvarez's code for creating the 2d matrix. I tried numerous ways including boost library but
    int **array2d = new int*[row];// I just couldnt get it to behave exactly like the way professor A. had it.
    for (int i = 0 ; i < row ; i ++) {
        array2d[i] = new int[col];
        for (int j = 0 ; j < col ; j ++) {
            array2d[i][j] = *(arr + index);
            index++;
        }
    }
  return array2d;
}
//******************************End Creating array*************************

//******************************Remove 2d array**********************************************
void remove_2darray(int **array2d, int row) {
    for (int i = 0 ; i < row ; i ++) {
        delete [] array2d[i];
    }
    delete [] array2d;
}
//********************************End deleting array*************************

//*********************************START Sudoku Calculations**********************************

//Searches the entire sudoku puzzle for the first instance of a 0 that appears.
bool findZero(int **arr, int &r, int &c) {
    for (r = 0; r < 9; r++){
        for (c = 0; c < 9; c++){
            if (arr[r][c] == 0){
                return true;
            }
        }
    }
    return false;
}
//*************************************Check Row Begins*******************************************
//This checks to see if the number is a valid candidate to being in it's respective row.
bool checkR(int **arr, int r, int temp) {
    for (int c = 0; c < 9; c++)
        if (arr[r][c] == temp)
            return true;
    return false;
}
//***************************************Check Row Ends******************

//**************************************Check Column Begins****************************************
//This checks to see if the number is a valid candidate to being in it's respective column.
bool checkC(int **arr, int c, int temp) {
    for (int r = 0; r < 9; r++)
        if (arr[r][c] == temp)
            return true;
    return false;
}
//*****************************************Check Column Ends***************

//******************************************Check Box Begins*****************************************
//This checks to see if the number is a valid candidate to being in it's respective box.
bool checkbox(int **arr, int startingR, int startingC, int temp){
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (arr[r+startingR][c+startingC] == temp)
                return true;
    return false;
}
//*******************************************Check Box Ends*******************

//****************************************Begin Solving (parent function)*************************
//This function takes the array in whatever state it's in to recursively try solutions.
bool solver(int **arr){
    int r;//row
    int c;//col
    bool found = findZero(arr, r, c);
    if(!found){    // This checks to see whether the puzzle is done or not.
       return true;
    }
    for (int test = 1;  test < 10; ++test){
        //checks the row, column and box to see if it's a valid place to test the current test value (1-9)
        bool valid = !checkC(arr, c, test) && !checkR(arr, r, test) && !checkbox(arr, r - r%3 , c - c%3, test);
        if(valid){
            arr[r][c] = test;
            if(solver(arr)){
                return true;
            }
            arr[r][c] = 0; // This is the backtracking step
        }
    }
    return false;
}
//**********************************End Solving(parent function)****************

//******************************Main function begins*****************************************
int main(int argc, char *argv[]){
    int numsArr[100];  //Store the input file in an array of ints.

//**************************OPEN FILE********************************************************
    int index = 0;
    char c;

    std::fstream myfile;
    myfile.open(argv[1]);
    if (!myfile){ std::cerr << "Can't open input file!";} //Error check to see if valid file
    else {
        while(!myfile.eof()){
            myfile >> c;
            if(c != ','){
                numsArr[index] = c-'0'; // converts the file char to an int and stores it in intArr.
                index++;
            }
        }
    }
    myfile.close();

//*****************************DONE WITH FILE*************************************
    int **array2d = matrix(numsArr, 9, 9);

//*********************************Print*****************************************************
    if (solver(array2d) == true){
        for (int r = 0; r < 9; r++){
            for (int c = 0; c < 9; c++){
                if(c != 8){
                   std::cout<< array2d[r][c]<< ',';
                } else {
                    std::cout<< array2d[r][c];
                }
            }
            std::cout<<'\n';
        }
    }
//************************************Print End*****************************
    remove_2darray(array2d, 9);
}
//*********************************End of Main and Source Code**************************************************************