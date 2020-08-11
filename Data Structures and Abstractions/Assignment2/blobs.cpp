#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>


//********************************* Create 2d Matrix function*******************************
int **matrix(int *arr, int row, int col){
    int index = 0;  //I borrowed Prof Alvarez's code for creating the 2d matrix. I tried numerous ways including boost library but
    int **array2d = new int*[row];// I just couldnt get it to behave exactly like the way professor A. had it.
    for (int i = 0 ; i < row ; i ++) {
        array2d[i] = new int[col];
        for (int j = 0 ; j < col ; j ++) {
            array2d[i][j] = *(arr + index);
            index++;
        }
    }

  // print
  /*for (int i = 0 ; i < row ; i ++) {
        for (int j = 0 ; j < col ; j ++) {
            std::cout << array2d[i][j] << ' ';
        }
        std::cout << std::endl << std::endl;
    }*/

  return array2d;
}

//**************************************End creating 2d Array******************

//******************************Deallocate************************************************
void remove_2darray(int **array2d, int row) {
    for (int i = 0 ; i < row ; i ++) {
        delete [] array2d[i];
    }
    delete [] array2d;
}
//*************************************Done Deallocate**************

//******************************************Changing Blobs*************************************
void changeBlobs(int **arr, int row, int col, int startR, int startC, int contype, int *count){
    if(contype == 4){
        if(startR != -1 && startC != -1 && startC != col && startR != row){ // This only checks if the connectivity type is 4
            if(arr[startR][startC] == 1){
                arr[startR][startC] = 2;
                changeBlobs(arr, row, col, startR+1, startC, contype, count);
                changeBlobs(arr, row, col, startR, startC+1, contype, count);
                changeBlobs(arr, row, col, startR-1, startC, contype, count);
                changeBlobs(arr, row, col, startR, startC-1, contype, count);
            }
        }
    } else if(contype == 8) { // This only checks if the conectivity type is 8.
        if(startR != -1 && startC != -1 && startC != col && startR != row){ // makes sure that the checks stay within bounds
            if(arr[startR][startC] == 1){// of the board
                arr[startR][startC] = 2;
                changeBlobs(arr, row, col, startR+1, startC, contype, count);
                changeBlobs(arr, row, col, startR, startC+1, contype, count);
                changeBlobs(arr, row, col, startR-1, startC, contype, count);
                changeBlobs(arr, row, col, startR, startC-1, contype, count);
                changeBlobs(arr, row, col, startR+1, startC+1, contype, count);
                changeBlobs(arr, row, col, startR+1, startC-1, contype, count);
                changeBlobs(arr, row, col, startR-1, startC+1, contype, count);
                changeBlobs(arr, row, col, startR-1, startC-1, contype, count);
            }
        }
    }
}

//*****************************************Changing Blobs Ends**************

//********************************Counting Blobs Starts**************************************
void countBlobs(int **arr, int row, int col, int contype, int *count){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(arr[i][j] == 1){
                int startR = i;
                int startC = j;
                changeBlobs(arr, row, col, startR, startC, contype, count);
                count[0]+=1;
            }
        }
    }
}
//********************************Counting Blobs Ends**************************

//**************************************MAIN FUNCTION****************************************
int main(int argc, char *argv[]){
    int count[1] = {0};
    int numsArr[5000];  //Store the input file in an array of ints.(1's and 0's)
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);

//**************************OPEN FILE********************************************************
    int index = 0;
    char c;     //Variables used in file opening and conversions
    int b;

    int contype = atoi(argv[4]);

    std::ifstream myfile;
    myfile.open(argv[1]);
    if (!myfile){ std::cerr << "Can't open input file!";} //Error check to see if valid file
    else {
        while(!myfile.eof()){
            myfile >> c;
            numsArr[index] = c-'0'; // converts the file char to an int and stores it in intArr.
            index++;
        }
    }

    myfile.close();
//*****************************DONE WITH FILE*************************************
    int **array2d = matrix(numsArr, row, col);
    countBlobs(array2d, row, col, contype, count);
    remove_2darray(array2d, row);
    std::cout << count[0] << std::endl;
}