#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>

//So essentially how my program works, is it takes an input file, translates the info into a 2d array,
//Then recursively changes every "1" into a "2" and incremements count ( an array of 1 number passed into the recursive function),
// This makes keeping track of the number of cells easier I feel since I don't have a number that get's recursively called,
// instead I increment the number in the array which is passed using pointers.
// So while my algorithm checks for 1's every 1 seen before would have already been labelled as see, aka "2" and not be
// counted again. This let's the algorithm recursively flow through the 2d array and get us our answer.
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
    for (int i = 0 ; i < row ; i ++) {//Delete 2d array from heap function.
        delete [] array2d[i];
    }
    delete [] array2d;
}
//*************************************Done Deallocate**************

//******************************************Count Cells*************************************
void countCells(int **arr, int row, int col, int startR, int startC, int contype, int *count){
    if(contype == 4){
        if(startR != -1 && startC != -1 && startC != col && startR != row){ // This only checks if the connectivity type is 4
            if(arr[startR][startC] == 1){
                count[0]+=1;
                arr[startR][startC] = 2;
                countCells(arr, row, col, startR+1, startC, contype, count);
                countCells(arr, row, col, startR, startC+1, contype, count);
                countCells(arr, row, col, startR-1, startC, contype, count);
                countCells(arr, row, col, startR, startC-1, contype, count);
            }
        }
    } else if(contype == 8) { // This only checks if the conectivity type is 8.
        if(startR != -1 && startC != -1 && startC != col && startR != row){ // makes sure that the checks stay within bounds
            if(arr[startR][startC] == 1){// of the board
                count[0]+=1;
                arr[startR][startC] = 2;
                countCells(arr, row, col, startR+1, startC, contype, count);
                countCells(arr, row, col, startR, startC+1, contype, count);
                countCells(arr, row, col, startR-1, startC, contype, count);
                countCells(arr, row, col, startR, startC-1, contype, count);
                countCells(arr, row, col, startR+1, startC+1, contype, count);
                countCells(arr, row, col, startR+1, startC-1, contype, count);
                countCells(arr, row, col, startR-1, startC+1, contype, count);
                countCells(arr, row, col, startR-1, startC-1, contype, count);
            }
        }
    }
}


//*****************************************Counting Cells Ends**************

//**************************************MAIN FUNCTION****************************************
int main(int argc, char *argv[]){
    int count[1] = {0};
    int numsArr[2000];  //Store the input file in an array of ints.(1's and 0's)
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);
    int startR = atoi(argv[4]) - 1;
    int startC = atoi(argv[5]) - 1;

//**************************OPEN FILE********************************************************
    int index = 0;
    char c;     //Variables used in file opening and conversions
    int b;

    int contype = atoi(argv[6]);

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
    countCells(array2d, row, col, startR, startC, contype, count);
    remove_2darray(array2d, row);
    std::cout << count[0] << std::endl;

}