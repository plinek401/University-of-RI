#include "list.h"
//#include "list.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <stdio.h>

int main (int argc, char **argv) {
    // Creates new list;
    List PDB = List();
    std::vector<std::string> v;
    // opening a text file (filename is passed as the first command line argument)
    std::ifstream myfile(argv[1]);
    std::string s;
    // read the file contents line-by-line
    while (std::getline(myfile, s)) {
    //I was really struggling to open the file due to the weird spacing
    //I've tried using the boost library, i've tried writing my own method which took the file line by line,
    // then i took the line character by character, appending to a string called word which i then appended to a
    //vector, where I then cleared the "word" string. This all failed, eventually I found a few lines of code, using the sstream library online
    //which made the white space irrelevant, which is the code you see below.
    //It's used to open the file and I works using any specifications such as only "ATOM" and only "CA" in their respective lines.
        std::istringstream iss(s);
        for(std::string s; iss >> s; )
             v.push_back(s);
        //Appends the new node
        if(v[0] == "ATOM" && v[2] == "CA"){
            std::string temp;
            temp = v[4];
            char c = temp[0];
            PDB.append(stod(v[6]), stod(v[7]), stod(v[8]), c);
        }
        v.clear();
    }
    myfile.close();

    PDB.euclydeanDistAndWrite();
}
