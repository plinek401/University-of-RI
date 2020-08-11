#include<iostream>

// you can save this file as functions.cpp
// this file (as is) should compile with no errors on Gradescope

// TODO
// add any required `include` directives here

// TODO
// add any other helper function here

unsigned long long int pow(int n, int n2){
    unsigned long long int result = 1;
    for(int i = 0; i < n2; i++){
        result = result *n;
    }
    return result;
}

bool checkPrime(int n){ // function to check if a num is prime
    bool testprime = true;
    for(int i = 2; i <= n / 2; ++i){
      if(n % i == 0){
          testprime = false;
          break;
       }
   }
    return testprime;
}
void sort_three(int a, int b, int c, int *list){
    if(a == b && a == c){
        list[0] = a;
        list[1] = b;
        list[2] = c;
    }
    if(a > b && a > c){
        list[0] = a;
        if(b >= c){
            list[1] = b;
            list[2] = c;
        } else{
            list[1]= c;
            list[2] = b;
        }
    }
    if(b > a && b > c){
        list[0] = b;
        if(a >= c){
            list[1] = a;
            list[2] = c;
        } else{
            list[1]= c;
            list[2] = a;
        }
    }
    if(c > b && c > a){
        list[0] = c;
        if(b >= a){
            list[1] = b;
            list[2] = a;
        } else{
            list[1]= a;
            list[2] = b;
        }
    }
 return;
}

unsigned int str_search(const char *pattern, const char *text){
    unsigned int count = 0;
    unsigned int lengthPattern = 0;
    unsigned int lengthText = 0;

    while (pattern[lengthPattern] != '\0') lengthPattern++; //figures out the length of the text
    while (text[lengthText] != '\0') lengthText++;  //figure out the length of the text
    
    for(unsigned int i = 0; i < (lengthText - lengthPattern + 1); i++){ // this loop goes through the entire text variable incrememnting by one, and making sure that at the enf of text, ana isnt being compared to just the a in "banana" 
    bool match = true;
        for(unsigned int j = 0; j < lengthPattern + i; j++){
            if(pattern[j] != text[i+j]){ // this code checks each letter in "ana" against each letter, three at a time from "ana ate the banana". For example, a = a, a!=' ', a = a, from the check of "ana" to "an|a a|te"
                match = false;
            }
            if(j == lengthPattern-1 && match){ // My check which determines whether or not (for example) "ana" matches the 3 letters in every triplet in "ana ate the banana"
                count++;
            }
        }
    }
    return count;
}

unsigned long int any2dec(const char *num, unsigned int b){
    char list[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int numlist[16] = {0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15};
    int newnumList[2000];
    int lengthnum = 0;
    unsigned long int finalNum = 0;

    while (num[lengthnum] != '\0') lengthnum++; //figures out the length of the text

    for(int i = 0; i < lengthnum; i++){ // inserts into a new array, newnumList, the integer values of the hexadecimal characters.
        for(int j = 0; j < 16; j++){
            if(num[i] == list[j]){
                newnumList[i] = numlist[j];
            }
        }
    }
     for (int i = 0; i < (lengthnum / 2); i++) {    //swaps the array holding the integer values of the hexadecimal characters to make further calculations easier.
        int temp = newnumList[i];
        newnumList[i] = newnumList[(lengthnum - 1) - i];
        newnumList[(lengthnum - 1) - i] = temp;
    }

    for(int j = 0; j < lengthnum; j++){
        if(j == 0){
            finalNum = finalNum + newnumList[j];
        } else {
            finalNum = finalNum + newnumList[j]*pow(b, (j));
        }
    }
    return finalNum;
}
void hex2rgb(const char *hex, char *rgb){
    int red;
    int green;
    int blue;
    char ArrayR[3];
    char ArrayG[3];
    char ArrayB[3];
    ArrayR[0] = hex[1];
    ArrayR[1] = hex[2];
    ArrayG[0] = hex[3];
    ArrayG[1] = hex[4];
    ArrayB[0] = hex[5];
    ArrayB[1] = hex[6];

    red = any2dec(ArrayR, 16);
    green = any2dec(ArrayG, 16);
    blue = any2dec(ArrayB, 16);

    int rednumDigits = 0;
    int greennumDigits = 0;
    int bluenumDigits = 0;

    if(red >=100){
        rednumDigits = 3;
    } else if (red >=10 && red < 100){
        rednumDigits = 2;
    } else {
        rednumDigits = 1;
    }
    if(green >=100){
        greennumDigits = 3;
    } else if (green >=10 && green < 100){
        greennumDigits = 2;
    } else {
        greennumDigits = 1;
    }
    if(blue >=100){
        bluenumDigits = 3;
    } else if (blue >=10 && blue < 100){
        bluenumDigits = 2;
    } else {
        bluenumDigits = 1;
    }
//*******************************************FORMATTING OF RGB STARTS*************************************************************
    rgb[0] = 'r';
    rgb[1] = 'g';
    rgb[2] = 'b';
    rgb[3]=  '(';

    int currentloc = 3;

        if(rednumDigits == 3){
            rgb[currentloc + 1] = '0' + (red / 10 / 10 % 10);
            rgb[currentloc + 2] = '0' + (red /10 % 10);
            rgb[currentloc + 3] = '0' + (red % 10);
            currentloc += 3;
        } else if (rednumDigits == 2){
            rgb[currentloc + 1] = '0' + (red / 10 % 10);
            rgb[currentloc + 2] = '0' + (red % 10);
            currentloc += 2;
        } else {
            rgb[currentloc + 1] = '0' + (red % 10);
            currentloc += 1;
        }

        rgb[currentloc + 1] = ',';
        currentloc += 1;

        if(greennumDigits == 3){
            rgb[currentloc + 1] = '0' + (green / 10 / 10 % 10);
            rgb[currentloc + 2] = '0' + (green /10 % 10);
            rgb[currentloc + 3] = '0' + (green % 10);
            currentloc += 3;
        } else if (greennumDigits == 2){
            rgb[currentloc + 1] = '0' + (green / 10 % 10);
            rgb[currentloc + 2] = '0' + (green % 10);
            currentloc += 2;
        } else {
            rgb[currentloc + 1] = '0' + (green % 10);
            currentloc += 1;
        }

        rgb[currentloc + 1] = ',';
        currentloc += 1;

        if(bluenumDigits == 3){
            rgb[currentloc + 1] = '0' + (blue / 10 / 10 % 10);
            rgb[currentloc + 2] = '0' + (blue /10 % 10);
            rgb[currentloc + 3] = '0' + (blue % 10);
            currentloc += 3;
        } else if (bluenumDigits == 2){
            rgb[currentloc + 1] = '0' + (blue / 10 % 10);
            rgb[currentloc + 2] = '0' + (blue % 10);
            currentloc += 2;
        } else {
            rgb[currentloc + 1] = '0' + (blue % 10);
            currentloc += 1;
        }

        rgb[currentloc + 1] = ')';
	   currentloc += 1;

	rgb[currentloc + 1] = '\0';
        
//****************************************************************************************************************
}
bool same_gmail(const char *g1, const char *g2){
    int length1 = 0;
    int length2 = 0;
    while (g1[length1] != '\0') length1++; //figures out the length of the first gmail
    while (g2[length2] != '\0') length2++; //figures out the length of the second email

    //***************************************Check if Valid Gmails************************
    bool Valid1;
    bool Valid2;

    //Tests string 1 to see if it's a valid gmail.
    if(g1[length1-10] == '@' && g1[length1-9] == 'g' || g1[length1-9] == 'G'){
        if(g1[length1-8] == 'm' || g1[length1-8] == 'M' && g1[length1-7] == 'a' || g1[length1-7] == 'A'){
            if(g1[length1-6] == 'i' || g1[length1-6] == 'I' && g1[length1-5] == 'l' || g1[length1-5] == 'L'){
                if(g1[length1-4] == '.' && g1[length1-3] == 'c' || g1[length1-3] == 'C'){
                    if(g1[length1-2] == 'o' || g1[length1-2] == 'O' && g1[length1-1] == 'm' || g1[length1-1] == 'M'){
                        Valid1 = true;
                    }
                }
            }
        }
    }
    // Tests string 2 to see if it's a valid gmail.
    if(g2[length2-10] == '@' && g2[length2-9] == 'g' || g2[length2-9] == 'G'){
        if(g2[length2-8] == 'm' || g2[length2-8] == 'M' && g2[length2-7] == 'a' || g2[length2-7] == 'A'){
            if(g2[length2-6] == 'i' || g2[length2-6] == 'I' && g2[length2-5] == 'l' || g2[length2-5] == 'L'){
                if(g2[length2-4] == '.' && g2[length2-3] == 'c' || g2[length2-3] == 'C'){
                    if(g2[length2-2] == 'o' || g2[length2-2] == 'O' && g2[length2-1] == 'm' || g2[length2-1] == 'M'){
                        Valid2 = true;
                    }
                }
            }
        }
    }
    //****************************************Ends Check of Valid Gmails********************
    char tempg1[length1-10];
    char tempg2[length2-10];

    //******Creates temp arrays that store only the relevant info, nthing between + signs and no .'s***
    if(Valid1 && Valid2){

        bool plusSeen = false;
        int incCount = 0;

        for(int i = 0; i < length1-10; i++){
            if(g1[i] == '+' && !plusSeen){  // used to check if the current index is between a + sign
                plusSeen = true;
            }
            if(g1[i] != '.' && g1[i] != '+' and !plusSeen){
                tempg1[incCount] = g1[i];
                incCount++;
            }
        }
        tempg1[incCount] = '\0';
        plusSeen = false;
        incCount = 0;
        for(int i = 0; i < length2-10; i++){
            if(g2[i] == '+' && !plusSeen){
                plusSeen = true;
            }
            if(g2[i] != '.' && g2[i] != '+' and !plusSeen){
                tempg2[incCount] = g2[i];
                incCount++;
            }
        }
        tempg2[incCount] = '\0';
    }
    else{
        return false;
    }
    //*************************End creating temp arrays*****************************

    //**********************Beginning of Comparing temp arrays****************************
    bool finalbool = true;
    length1 = 0;
    length2 = 0;
    while (tempg1[length1] != '\0') length1++; //figures out the length of the first temp array
    while (tempg2[length2] != '\0') length2++; //figures out the length of the second temp array

    if(length1 != length2){ //If the remaining temp strings arent equal lengths return false as they
    //won't be the same string in that case
        return false;
    } else {
        for(int i = 0; i < length1; i++){
            //Checks to see if the current index is a letter
            if(((int)tempg1[i] >= 65 && (int)tempg1[i] <= 90 && (int)tempg2[i] >= 65 && (int)tempg2[i] <= 90)||
               ((int)tempg1[i] >= 97 && (int)tempg1[i] <= 122 && (int)tempg2[i] >= 65 && (int)tempg2[i] <= 90) ||
               ((int)tempg1[i] >= 65 && (int)tempg1[i] <= 90 && (int)tempg2[i] >= 97 && (int)tempg2[i] <= 122) ||
               ((int)tempg1[i] >= 97 && (int)tempg2[i] <= 122 && (int)tempg2[i] >= 97 && (int)tempg2[i] <= 122)) {

                //Checks each letter to see if theyre equal to each other, includes checks on capitalization.
                    if(     (int)tempg1[i] == (int)tempg2[i] ||
                        ((int)tempg1[i] <= 90 && (int)tempg2[i] == (int)tempg1[i] + 32) ||
                        ((int)tempg1[i] >= 97 && (int)tempg2[i] == (int)tempg1[i] - 32) ||
                        ((int)tempg2[i] <= 90 && (int)tempg1[i] == (int)tempg2[i] + 32) ||
                        ((int)tempg2[i] >= 97 && (int)tempg1[i] == (int)tempg2[i] - 32)){

                }
                else{
                    finalbool = false;
                }
            }
            else if(tempg1[i] != tempg2[i]){ // if the index of the parent gmail isn't a letter, and it's not even return false
                        finalbool = false;
            }
        }
    }
    //*********************End comparing temp arrays**********************************
    return finalbool;
}unsigned int unique_letters(const char *S){
    unsigned int length = 0;
    unsigned int count = 0;

    while (S[length] != '\0') length++; //figures out the length of the text

    for(unsigned int i = 0; i < length; i++){
        bool seen = false;
        bool entered = false;
        if((int)S[i] >= 65 && (int)S[i] <= 90 || (int)S[i] >= 97 && (int)S[i] <= 122){ // checks to see if the current "pointer" is a letter by checking their ascii values.
            entered = true;
            for(unsigned int j = 0; j < i; j++){
                if((int)S[i] == (int)S[j] || (int)S[i] <= 90 && (int)S[j] == (int)S[i] + 32 || (int)S[i] >= 97 && (int)S[j] == (int)S[i] - 32 ){ //Check to make sure you dont count capital letters as unique.
                    seen = true;
                    break;
                }
            }
        }
        if(!seen && entered){
            count++;
        }
    }

    return count;
}
void toswap(int *first, int *second)
{
    int temp = *first;  //a sort function called by the n_inversions function.
    *first = *second;
    *second = temp;
}


unsigned int n_inversions(const int *A, unsigned int n){
    unsigned int inversions = 0;
    int cloned[1001]; // create a new array that's exactly identical to the original for the purposes of sorting.

    for(int k = 0; k < n; k++){
        cloned[k] = A[k];
    }

    for (int i = 0; i < n - 1; i++) {       //nested forloop to sort the nea "cloned" array, and each time it makes a swap, increment inversions which will let us know how many times
        for (int j = 0; j < n - i - 1; j++) {// the list was inverted from it being organized.
           if (cloned[j] > cloned[j+1]){
              toswap(&cloned[j], &cloned[j+1]);
              inversions ++;
           }
        }
    }
    return inversions;
}

unsigned int l_mode(const int *A, unsigned int n){
    unsigned int result;

    int mostOccured = 0;
    int numberMostOccured;

    for(int i = 0; i < n; i++){
         int occurances = 1;
        for(int j = i + 1; j < n; j++){
            if(A[i] == A[j]){
                occurances += 1;
            }
        }
        if(occurances > mostOccured){
            mostOccured = occurances;
            numberMostOccured = A[i];
        } else if (occurances == mostOccured){
            if(A[i] < numberMostOccured){
                numberMostOccured = A[i];
            }
        }
    }
    for(int k = 0; k < n; k++){
        if(A[k] == numberMostOccured){
            result = k;
            break;
        }
    }

    return result;
}
void to_hostname(char *address){
    int length = 0;
    int endHttp = 0;
    int i = 0;

    //Find length of the original url
    while(address[length] != '\0') length++;
    //find how long the hostname is "Https://", "ftp://" checks up to the double "//"

    for(int i = 0; i < length; i++){
        if(address[i] == '/' && address[i-1] == '/' && address[i-2] == ':'){
            endHttp = i + 1;
        }
    }
    while(address[endHttp] != ':' && address[endHttp] != '/' && address[endHttp] != '\0'){
        address[i] = address[endHttp];
        endHttp++;
        i++;
    }

    address[i] = '\0';

    //make all letters in address lower case.
    for(int j = 0; address[j]; j++){
        if((int)address[j] >= 65 && (int)address[j] <= 90){
            address[j] =(char)((int)address[j]+32);
        }else{
            address[j] = address[j];
        }
    }
}

bool circular_prime(unsigned int n) {
    unsigned int count = 0;
    unsigned int temp = n; // few variables

    if(n == 0 || n == 1){	//checks edge cases of 0 and 1
	   return false;
    } 

    while (temp) {
        count++;        //checks the length of the number
        temp /= 10;
    }

    int num = n;
    while(checkPrime(num)) {    //loop that begins to check if each cycle of the number is prime

        int modded = num % 10;  // modded is set to equal that last digit in num
        int divided = num / 10; //divided is then set as num / 10 aka without the last digit that is now stored in modded
        num = (pow(10, count - 1)) * modded + divided; // combines the last digit of num(now stored in modded) to the front of divided

       if(num == n){ // compares original number to num which rotates around.
            return true;
       }
    }
    return false;
}

long int unique_sums(const int *A, unsigned int n, unsigned int k) {
//I don't even know where to get started with this one :/
 return 0;
}

