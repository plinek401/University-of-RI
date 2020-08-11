#include <iostream>
#include <fstream>
#include <cstdlib>

//**************************Creating 2d array*********************************************
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
  return array2d;
}

bool **empty_solutions_grid(int row, int col) {
    bool **grid = new bool*[row];
    for (int i = 0 ; i < row ; i ++) {
        grid[i] = new bool[col];
        for (int j = 0 ; j < col ; j ++) {
            grid[i][j] = 0;
        }
    }
    return grid;
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

//********************************Find min and max start********************************
void findMin(int **arr, int row, int col, int *low){
    int min = arr[0][0];

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            if(arr[i][j] < min){
                min = arr[i][j];
                low[0] = i;//Stores the low points in an array passed by reference.
                low[1] = j;
            }
        }
    }
}

void findMax(int **arr, int row, int col, int *high){
    int max = arr[0][0];

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            if(arr[i][j] > max){
                max = arr[i][j];
                high[0] = i;//Stores the high points in an array passed by reference.
                high[1] = j;
            }
        }
    }
}
//*********************************Find min and max end********************

bool allPaths(int **arr, int row, int col, int startR, int startC, int seenR, int seenC, int *high, bool found, bool **path){
    if(startR == high[0] && startC == high[1]){ // Check to see if the path has reached the highest point.
        found = true;
    }

    if(!found){// calls new recursion if not found
        if(startR < row - 1){ // Keeps in Bound
            if(path[startR+1][startC] != 1){ // Checks to make sure the spot isn't the previous spot
                if(arr[startR+1][startC] > arr[startR][startC] || arr[startR+1][startC] == arr[startR][startC]){
                    path[startR][startC] = 1;
                    seenR = startR;
                    seenC = startC;
                    found = allPaths(arr, row, col, startR+1, startC, seenR, seenC, high, found, path); //DOWN
                }
            }
        }
    }
    if(!found){
        if(startC < col - 1){
            if(path[startR][startC+1] != 1){
                if(arr[startR][startC+1] > arr[startR][startC] || arr[startR][startC+1] == arr[startR][startC]){
                    path[startR][startC] = 1;
                    seenR = startR;
                    seenC = startC;
                    found = allPaths(arr, row, col, startR, startC+1, seenR, seenC, high, found, path);//RIGHT
                }
            }
        }
    }
    if(!found){
        if(startR > 0){
            if(path[startR-1][startC] != 1){
                if(arr[startR-1][startC] > arr[startR][startC] || arr[startR-1][startC] == arr[startR][startC]){
                    path[startR][startC] = 1;
                    seenR = startR;
                    seenC = startC;
                    found = allPaths(arr, row, col, startR-1, startC, seenR, seenC, high, found, path);//UP
                }
            }
        }
    }
    if(!found){
        if(startC > 0){
            if(path[startR][startC-1] != 1){
                if(arr[startR][startC-1] > arr[startR][startC] || arr[startR][startC-1] == arr[startR][startC]){
                    path[startR][startC] = 1;
                    seenR = startR;
                    seenC = startC;
                    found = allPaths(arr, row, col, startR, startC-1, seenR, seenC, high, found, path);//LEFT
                }
            }
        }
    }
    return found;
}

//*****************************Find Path End*********************************

//**************************************MAIN FUNCTION****************************************
int main(int argc, char *argv[]){
    char printN[3] = "no";
    char printY[4] = "yes";
    int numsArr[10000];  //Store the input file in an array of ints.
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);
    int low[2] = {0,0}; //stores the low value location, {row, col}
    int high[2] = {0,0};// stores the high value location, {row, col}

//**************************OPEN FILE********************************************************
    int index = 0;
    int b;

    std::ifstream myfile;
    myfile.open(argv[1]);
    if (!myfile){ std::cerr << "Can't open input file!";} //Error check to see if valid file
    else {
        while(myfile >> b){
          numsArr[index] = b;
          index++;
        }
    }
    myfile.close();

//*****************************DONE WITH FILE*************************************

    int **array2d = matrix(numsArr, row, col);
    bool **path2d = empty_solutions_grid(row, col);

    findMin(array2d, row, col, low);
    findMax(array2d, row, col, high);
    int startR = low[0];
    int startC =  low[1];
    bool found = allPaths(array2d, row, col, startR, startC, startR, startC, high, false, path2d);
    remove_2darray(array2d, row);

    if (found == 1){
        std::cout<< startR + 1 << " " << startC + 1 << " "<< high[0] + 1 << " " << high[1]+ 1 << " " << printY << std::endl;
    }else{
        std::cout<< startR + 1 << " " << startC + 1 << " "<< high[0] + 1 << " " << high[1]+ 1 << " " << printN << std::endl;
    }
}