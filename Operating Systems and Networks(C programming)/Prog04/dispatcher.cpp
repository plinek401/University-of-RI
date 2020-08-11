#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv){
    string inPath = argv[1];
    string outPath = argv[2];

    int countNumChildren = 0;
    //Instantiate string.
    string commandLineString;

    int numFailedExecutions = 0;

    int incrementer = 3;
    //Triple loop, first loop finds the first instance of "rotate, crop, split". The second loop finds the second. The thrid loop loops between the first loop value and the second loop value, appending the arguments for each call to a string.
    while(incrementer < argc){
        //Resets the string and appends it to the default input path, output path baseline arguments.
        commandLineString = "";
        commandLineString.append(inPath);
        commandLineString.append(" ");
        commandLineString.append(outPath);
        commandLineString.append(" ");
        if((strcmp(argv[incrementer], "rotate") == 0) || (strcmp(argv[incrementer], "crop") == 0) || (strcmp(argv[incrementer], "split") == 0)){
            for(int i = incrementer+1; i < argc; ++i){
                if((strcmp(argv[i], "rotate") == 0) || (strcmp(argv[i], "crop") == 0) || (strcmp(argv[i], "split") == 0)){
                    for(int j = incrementer; j < i; ++j){
                        commandLineString.append(argv[j]);
                        commandLineString.append(" ");
                    }
                    countNumChildren++;
                    //New Process Creation
                    int pid = fork();

                    if(pid == -1){
                        perror("fork");
                    }
                    if(pid == 0){
                        exec(commandLineString);

                    }
                    if(pid > 0){
                        wait(3);
                    }
                    break;
                }
            }
        }
        incrementer++;
    }



    return 0;
}
