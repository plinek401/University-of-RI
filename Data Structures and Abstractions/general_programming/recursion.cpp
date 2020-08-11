#include<iostream>

unsigned long int rec_suffix_sum(unsigned int n, unsigned int s){
    if(s == 0){
        return 0;
    }
    return n + rec_suffix_sum(n-1, s-1);
}

unsigned int rec_sum_even(unsigned int num){
    int temp = num;
    if(num == 0){
        return 0;
    } else {
        if((num % 10) % 2 == 0){
            return ((num % 10) + rec_sum_even(num / 10));
        } else {
            return rec_sum_even(num/10);
        }

    }
}

bool rec_is_sorted(const int *A, unsigned int n){
    if(n == 1){
        return true;
    }
    if(A[n-1] <= A[n-2]){
        return rec_is_sorted(A, n-1);
    } else{
        return false;
    }
}

bool rec_palindrome(const char *S, unsigned int n){
    if(n == 1 || n == 0){
        return true;
    }
    char temp[2000];
    for(int i = 1; i < n-1; i++){
        temp[i-1] = S[i];
    }
    if(S[0] == S[n-1]){
        return rec_palindrome(temp, n-2);
    } else {
        return false;
    }
}

void rec_reverse_str(char *str, unsigned int len){
    if(len > 1){
        char temp = str[0];
        str[0] = str[len - 1];
        str[len - 1] = temp;
        ++str;
        rec_reverse_str(str, len-2);
    }
}

bool rec_sorted_vowels(const char *A){
    int length = 0;
    while(A[length] != '\0') length++;

    char temp1[2000];
    char temp[2000];
    int index = 0;
    int count = 0;

    for(int i = 0; i < length; i++){
        if((int)A[i] > 64 && (int)A[i] < 91){   //Converts string to full lowercase.
            temp1[i] = (char)((int)A[i]+32);
        } else {
            temp1[i] = A[i];
        }
        count++;
    }
    temp1[count] = '\0';
    //if((int)A[0] > 96 && (int)A[0] < 123){ // Determine whether the string is all caps or all lower case
        for(int i = 0; i < length; i++){
            if((int)temp1[i] == 97 || (int)temp1[i] == 101 || (int)temp1[i] == 105 || (int)temp1[i] == 111 || (int)temp1[i] == 117){
                temp[index] = temp1[i]; //create temporary/the new array which holds only the vowels
                index++;
            }
        }
   temp[index] = '\0';

    int len = 0;
    while(temp[len] != '\0') len++;

    if(temp[0] == '\0' || temp[1] == '\0'){    //check to see if there are any vowels in string,
    // or if there is only 1 vowel return true in these cases.
        return true;
    }
//**********************I can finally start the recursion after that painstaking process*******************************
    if(temp[2] == '\0'){
        if((int)temp[0] <= (int)temp[1]){   // applies only if there are only 2 vowels in our string
            return true;
        } else {
            return false;
        }
    }

    if((int)temp[0] <= (int)temp[1] && (int)temp[1] <= (int)temp[2]){
        if(temp[3] == '\0'){
            return true;
        } else {
            for(int i = 1; i < len + 1; i++){
                temp[i-1] = temp[i];
            }
            temp[len] = '\0';
            rec_sorted_vowels(temp);
        }
    } else {
        return false;
    }
}

bool rec_bin_search(const int *A, unsigned int n, int k){
    if(n == 0){
        return false;
    }
    if(k == A[n/2]){
        return true;
    } else {
        if(k == A[n-1]){
            return true;
        }
        if(k > A[n/2]){
            rec_bin_search(A, n/2, k);
        } else if(k < A[n/2]){
            A = A + (n/2);
            rec_bin_search(A, n/2, k);
        }
    }
}

void rec_selection_sort(int *A, unsigned int n){
    int smallestnum = A[0];
    int index = 0;
    if(n > 0){
        for(int i = 1; i < n; i++){
            if(A[i] < smallestnum){
                smallestnum = A[i];
                index = i;
            }
        }
        int temp = A[0];
        A[0] = A[index];
        A[index] = temp;
        ++A;
        rec_selection_sort(A, n-1);
    }
}

int rec_check_order(const int *A, unsigned int n){
    if(n == 2){
        if(A[n-1] > A[n-2]){
            return 1;
        } else if (A[n-1] < A[n-2]){
            return -1;
        } else{
            return 0;
        }
    }
    if(A[n-3] < A[n-2] && A[n-2] < A[n-1]){
        if(n == 3){
            return 1;
        } else {
        rec_check_order(A, n-1);
        }
    } else if(A[n-3] > A[n-2] && A[n-2] > A[n-1]){
        if(n == 3){
            return -1;
        } else {
            rec_check_order(A, n-1);
        }
    } else {
        return 0;
    }
}

void rec_reversed_letters(const char *str){
    if(str[0] == '\0'){
        return;
    }
    int length = 0;
    while(str[length] != '\0') length++;
    char temp[2000];

    for(int i = 0; i < length; i++){
        temp[i] = str[i];
    }
    if((int)temp[length - 1] > 96 && (int)temp[length - 1] < 123){
    std::cout << temp[length - 1];
    }
    temp[length-1] = '\0';
    rec_reversed_letters(temp);
}