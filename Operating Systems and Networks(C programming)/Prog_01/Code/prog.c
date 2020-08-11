#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function simply returns a 0 if the parameter number is prime,
//and it returns 1 if the number isn't a prime.
int prime(int n){
    int valid = 0;

    if(n == 2){
        return valid;
    }
    else{
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0){
                valid = 1;
                break;
            }
        }
    }
    return valid;
}

char* get_program_name(char* str)
{
    int last_backslash = 0;
    int i = 0;
    char *name = (char *) malloc(3);
    //Determine where the last path delimiter '\' is to find program name.
    //On my environment at least the first argument was the entire path to the file.
    //Finds Index of last '\' character.
    while(str[i] != '\0'){
        if(str[i] == '\\'){
            last_backslash = i;
        }
        i++;
    }

    int start_str = 0;
    /*Loops through, beginning at the index of last backslash + 1, until
    the full program name is stored in a C-string*/
    for(int j = last_backslash+1; j < i; j++){
        name[start_str] = str[j];
        start_str++;
        if(i - j == 1){
            name[start_str] = '\0';
        }
    }
    return name;
}

void find_primes1(char* name, int amount)
{
    int count = 0;
    //Dynamically allocates enough memory to handle the maximum number of possible primes.
    int *primes = (int *)malloc(sizeof(int)*amount);

    //Checks to see if enough memory was allocated. Else outputs error and ends execution.
    if(primes == NULL) {
        printf("malloc of size %d failed!\n", amount);
    }
    else{
        if(amount < 1){
            printf("%s's argument is not a strictly positive integer.",name);
        }
        else{
            int i = 2;
            while(count < amount){
                if(prime(i) == 0){
                    primes[count] = i;
                    count++;
                }
            i++;
            }
            //Addresses the case that the user asks for the first prime number
            if(amount == 1){
                printf("The first prime number is ");
            }
            //Converts output message from "There are 4", to "There re four" as long as number is below 20.
            else if(amount < 20){
                char* numList[20] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten","eleven","twelve", "thirteen", "fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
                printf("The first %s prime numbers are: ", numList[amount-1]);
            }

            else{
                printf("The first %d prime numbers are: ",count);
            }
            for(int i = 0; i < count; i++){
                printf("%d", primes[i]);
                if(count - i == 1){
                    printf(".\n");
                }
                else{
                printf(",");
                }
            }
        }
        //Frees primes pointer array.
        free(primes);
    }
}
//This is the function that is called when the event of 2 arguments being entered into the command line is true. Pos is the variable that tells me which argument,
//argv[1] or argv[2] is larger and which one is smaller. Based on that I can determine from what to what numbers I'm looking for primes.
void find_primes2(char* name, int lower, int upper, int pos)
{
    if(lower < 1 && upper < 1){
        printf("Both of %s's arguments aren't strictly positive integers.\n", name);
    }
    else if(lower < 1){
        if(pos == 1){
            printf("%s's first argument is not a strictly positive integer.\n",name);
        }
        else{
            printf("%s's second argument is not a strictly positive integer.\n",name);
        }
    }
    else if (upper < 1){
        if(pos == 1){
            printf("%s's second argument is not a strictly positive integer.\n",name);
        }
        else{
            printf("%s's first argument is not a strictly positive integer.\n",name);
        }
    }
    else{//count keeps track of how many numbers there are between the 2 provided integers. Primes is a pre-allocated array.
        int count = 0;
        int *primes = (int *)malloc(sizeof(int)*(upper-lower));

        if(primes == NULL) {
            printf("malloc of size %d failed!\n", (upper-lower));
        }
        else{
            //This loop calls the prime function to check if the number is a prime or not, and if it is, it adds it to the primes list.
            for(int i = lower; i < upper; i++){
                if(i != 1){
                    if(prime(i) == 0){
                        primes[count] = i;
                        count++;
                    }
                }
            }//Below here are all the outputs and possibilities for the output. No primes, 1 prime, multiple primes, etc.
            if(count < 1){
                printf("There is no prime number between %d and %d.\n", lower, upper);

            }
            else if(count == 1){
                printf("There is only one prime number between %d and %d: %d\n", lower, upper, primes[0]);
            }
            else if(count > 1 && count < 20){
                char* numList[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten","eleven","twelve", "thirteen", "fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
                printf("There are %s prime numbers between %d and %d: ",numList[count-1], lower, upper);
            }
            else{
                printf("There are %d prime numbers between %d and %d: ",count, lower, upper);
            }
            if(count > 1){//This loop prints out the actual primes with proper formatting, commas in between characters and a period at the end.
                for(int i = 0; i < count; i++){
                    printf("%d", primes[i]);
                    if(count - i == 1){
                        printf(".\n");
                    }
                    else{
                        printf(", ");
                    }
                }
            }
            free(primes);
        }
    }
}

int main(int argc, char* argv[]){
    //Calls function to find program name.
    char* name = get_program_name(argv[0]);

    //Check arguments to see if there is enough arguments to proceed or generates an error.
    if(argc < 2){
        printf("%s launched with no argument.\nProper usage: prog m [n]\n",name);
    }//Checks 1 argument.
    else if(argc == 2){
        find_primes1(name,atoi(argv[1]));
    }//Checks 2 arguments
    else if(argc == 3){//Checks which argument is larger, the second or third.
        if(atoi(argv[1]) <= atoi(argv[2])){
            find_primes2(name,atoi(argv[1]),atoi(argv[2]),1);
        }
        else{
            find_primes2(name,atoi(argv[2]),atoi(argv[1]),2);
        }
    }
    else{//Otherwise too many arguments.
        printf("%s launched with too many arguments.\nProper usage: prog m [n]\n",name);
    }
    free(name);
}
