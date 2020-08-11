#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This struct holds the values of the start and end positions of each range. I know this isn't how it's supposed to be done but I couldn't figure
//out what the point of this "struct" feature was. It seemed to me like a glorified way to just store the same info I could've declared in the function.
struct Math{
    char rangeFrom1; // '*'
    char rangeTo1; // '+'

    char rangeFrom2; // !
    char rangeTo2; // !

    char rangeFrom3; // %
    char rangeTo3; // %

    char rangeFrom4; // -
    char rangeTo4; // -

    char rangeFrom5; // /
    char rangeTo5; // /

    char rangeFrom6; // =
    char rangeTo6; // =
};

struct Letter{
    char rangeFrom1;
    char rangeTo1;

    char rangeFrom2;
    char rangeTo2;
};

struct Number{
    char rangeFrom;
    char rangeTo;
};

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

//This is the comparator associated with the ascii qsort.
int comparator(const void *first, const void *second) {
  return *(char*)first - *(char*)second;
}
//This function does all the sorting including qsort for Ascii ordered sorting.
void sortAscii(char* input){
    //This is probably not how you want this done. However, I feel like
    struct Letter lt;
    lt.rangeFrom1 = 'a'; lt.rangeTo1 = 'z';
    lt.rangeFrom2 = 'A'; lt.rangeTo2 = 'Z';
    struct Number num;
    num.rangeFrom = '0'; num.rangeTo = '9';
    struct Math mt;
    mt.rangeFrom1 = '*'; mt.rangeTo1 = '+';
    mt.rangeFrom2 = '!'; mt.rangeTo2 = '!';
    mt.rangeFrom3 = '%'; mt.rangeTo3 = '%';
    mt.rangeFrom4 = '-'; mt.rangeTo4 = '-';
    mt.rangeFrom5 = '/'; mt.rangeTo5 = '/';
    mt.rangeFrom6 = '='; mt.rangeTo6 = '=';

    //Length variable of input
    int len = strlen(input);

    //Create 4 temporary c-arrays. One for lower case letters, one for upper case letters, one for numbers, one for symbols. Each having a count.
    char upper[len];
    int countU = 0;
    char lower[len];
    int countL = 0;
    char nums[len];
    int countN = 0;
    char math[len];
    int countM = 0;
    char others[len];
    int countO = 0;

    //Loop through and place each character into appropriate sub array to be sorted individually.
    for(int i = 0; i < len; ++i){
        if(input[i] >= num.rangeFrom && input[i] <= num.rangeTo){
            nums[countN] = input[i];
            countN++;
        }
        else if((input[i] >= mt.rangeFrom1&& input[i] <= mt.rangeTo1)|| (input[i] >= mt.rangeFrom2 && input[i] <= mt.rangeTo2) || (input[i] >= mt.rangeFrom3 && input[i] <= mt.rangeTo3) || (input[i] >= mt.rangeFrom4&& input[i] <= mt.rangeTo4) || (input[i] >= mt.rangeFrom5&& input[i] <= mt.rangeTo5) || (input[i] >= mt.rangeFrom6&& input[i] <= mt.rangeTo6)){
            math[countM] = input[i];
            countM++;
        }
        else if(input[i] >= lt.rangeFrom1 && input[i] <= lt.rangeTo1){
            lower[countL] = input[i];
            countL++;
        }
        else if(input[i] >= lt.rangeFrom2&& input[i] <= lt.rangeTo2){
            upper[countU] = input[i];
            countU++;
        }
        else{
            others[countO] = input[i];
            countO++;
        }
    }
    upper[countU] = '\0';
    lower[countL] = '\0';
    nums[countN] = '\0';
    others[countO] = '\0';
    math[countM] = '\0';

    //Get number of each subsection.
    int lenU = strlen(upper); int lenL = strlen(lower); int lenN = strlen(nums); int lenO = strlen(others); int lenM = strlen(math);

    //Call qsort non each subsection.
    qsort(upper, lenU, sizeof(char), comparator);
    qsort(lower, lenL, sizeof(char), comparator);
    qsort(nums, lenN, sizeof(char), comparator);
    qsort(others, lenO, sizeof(char), comparator);
    qsort(math, lenM, sizeof(char), comparator);

    int counter = 0;
    //Combine each subsection, upper letters first, then lower, then nums then symbols back into original input.
    for(int i = 0; i < lenN; ++i){
        input[counter] = nums[i];
        counter++;
    }
    for(int i = 0; i < lenM; ++i){
        input[counter] = math[i];
        counter++;
    }
    for(int i = 0; i < lenU; ++i){
        input[counter] = upper[i];
        counter++;
    }
    for(int i = 0; i < lenL; ++i){
        input[counter] = lower[i];
        counter++;
    }
    for(int i = 0; i < lenO; ++i){
        input[counter] = others[i];
        counter++;
    }

    input[len] = '\0';
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
            //sort(input);
            sortAscii(input);

            printf("\"%s\"\n", input);
        }
    }
    free(input);
    input = NULL;

    return 0;
}
