#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void remove_duplicates(char* input){

    int len = strlen(input);
    //Creates a temporary list to hold unique characters from our input string.
    char temp[100];
    temp[0] = input[0];
    //Keeps track of how long our temp array is.
    int count = 1;
    //Enters a nested for loop. The outer loop loops through our input string. while our inner loop loops through the temp string.
    //The loops check each input character against our temp characters. If there exists the input character in the temp array then the loop breaks and the
    //next character is checked. If the input character is not in the temp array, then the character gets added to the end of the array.
    //This loop removes duplicate characters including spaces, tabs and special characters.
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < count; ++j){
            if(input[i] == temp[j]){
                break;
            }
            if(j == count - 1){
                temp[count] = input[i];
                count++;
            }
        }
    }
    //Dont forget to add the '\0' character to the end of our c-string :^)
    temp[count] = '\0';

    //copies the temp array into the input array. removing the characters "in place".
    for(int i = 0; i < count+1; ++i){
        input[i] = temp[i];
    }
}

//Sort takes a string that has only 1 of each character. (gets called after "remove_duplicates" function.
void sort(char* input){
    //variables
    int len = strlen(input);
    char* output = (char*)malloc(len);
    int chars = 0; int nums = 0; int others = 0;
    //loop determines how many chars, nums and other symbols there are.
    for(int count = 0; count < len; ++count){
        if ((input[count] >= 'a' && input[count] <= 'z') || (input[count] >= 'A' && input[count] <='Z')){
            chars++;
        }
        else if(input[count] >= '0' && input[count] <= '9'){
            nums++;
        }
        else{
            others++;
        }
    }
    //pointers pointing where chars, nums and other symbols begin to be inserted.
    char* charptr = output;
    char* numptr = output+chars;
    char* otherptr = output+chars+nums;
    //loop that goes through and sorts chars, nums and others. Has 3 pointers pointing where the chars start, nums starts and others start.
    for(int i = 0; i < len; ++i){
        if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <='Z')){
            *charptr = input[i];
            charptr++;
        }
        else if(input[i] >= '0' && input[i] <= '9'){
            *numptr = input[i];
            numptr++;
        }
        else{
            *otherptr = input[i];
            otherptr++;
        }
    }
    //Can't forget string terminating character.
    *otherptr = '\0';

    for(int i = 0; i < len; ++i){
        input[i] = output[i];
    }
    //Free memory and null pointers.
    free(output); output = NULL; charptr = NULL; numptr = NULL; otherptr = NULL;
}


int main(){
    //Allocate a 100 character long array in the heap which will be passed and altered in place and outputted.
    //I'm not fully sure how to allocate dynamically the appropriate amount of space for strings without creating a whole class for it.
    //But seeing as this is c and not c++ then I'm not sure. Cause I need to have a length of how long the input is, but I need the memory allocated
    //to store the string ti find the length of.
    char* input = (char*)malloc(100);
    //Scanf allows input for any characters including white space.
    while(1){
        printf("Enter an input string: ");
        scanf(" %[^\n]", input);

        int len = strlen(input);
        //Checks for exit condition. Input string being 'EXIT'
        if(len == 4 && input[0] == 'E' && input[1] == 'X' && input[2] == 'I' && input[3] == 'T'){
            break;
        } else{
            //Function calls
            remove_duplicates(input);
            sort(input);

            printf("\"%s\"\n", input);
        }
    }
    free(input);
    input = NULL;

    return 0;
}
