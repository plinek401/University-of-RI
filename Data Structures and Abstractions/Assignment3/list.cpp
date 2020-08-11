#include <iostream>
//#include <cstdlib>
#include "list.h"
#include <math.h> //used for euclydean distance
#include <fstream>

List::List(){
    head = NULL;
    tail = NULL;
    size = 0;
}

List::~List(){
    clear();
    //std::cout<<"Deleted"<<std::endl;
}

void List::append(double a, double b, double c, char ch){
    node *end = new node();
    end->x = a;
    end->y = b;
    end->z = c;
    end->chain = ch;
    end->next = NULL;

    if(head == NULL){
        head = end;
        tail = end;
    } else {
        node *temp = tail;
        tail = end;
        temp->next = end;
    }
    size++;
}

void List::prepend(double a, double b, double c, char ch){
    node *start = new node();
    start->x = a;
    start->y = b;
    start->z = c;
    start->chain = ch;
    start->next = head;

    if(head == NULL){
        head = start;
        tail = start;
    } else {
        head = start;
    }
    size++;
}

void List::print(){
    node *temp = head;
    while(temp != NULL){
        std::cout << '(' << temp->x << ',' << temp->y << ','<< temp->z << ')' << temp->chain << ' ';
        std::cout<<std::endl;
        temp = temp->next;
    }
}

void List::clear(){
    for(int i = 0; i < size; ++i){
        node *temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

void List::euclydeanDistAndWrite(){
    std::ofstream myfile;
    std::ofstream myfileCol;
    myfile.open ("coords.js");
    myfile << "var coords = [" << "\n";
    myfile.close();
    myfileCol.open("colors.js");
    myfileCol << "var colors =[" << "\n";
    myfileCol.close();

    double shortx;
    double shorty;
    double shortz;
    node* colTemp;

    node *temp = head;
    node *temp2 = head;
    double shortest;
    for(int i = 0; i < size; ++i){//May be 1 off error, CARE
        //Random default "shortest", could be made more dynamic.
        shortest = 10000;
        for(int j = 0; j < size; ++j){ //May be 1 off error, CARE
            if(temp != temp2){
                //Calculate the Euclydean Distance here, stored in the variable dist.
                double xd = (temp->x - temp2->x) * (temp->x - temp2->x);
                double yd = (temp->y - temp2->y) * (temp->y - temp2->y);
                double zd = (temp->z - temp2->z) * (temp->z - temp2->z);
                double dist = sqrt(xd + yd + zd);

                if(dist < shortest){
                    colTemp = temp2;
                    shortest = dist;
                    shortx = temp2->x;
                    shorty = temp2->y;
                    shortz = temp2->z;
                }
            }
            temp2 = temp2->next;
        }
//---------------------------------------------------------------------------
        /*DO WRITING TO FILE STUFF HERE */

        myfile.open ("coords.js", std::ios_base::app);
        myfile << temp->x << ", "  << temp->y << ", " << temp->z << ", " << shortx << ", " << shorty << ", " << shortz << ",\n" ;
        myfile.close();


//The struggle to create the file of color RGB values.
        if(temp->chain == 'A'){
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 0 << ", " << 0 << ", " << 1 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }

        else if(temp->chain == 'B'){
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 0 << ", " << 1 << ", " << 0 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }

        else if(temp->chain == 'C'){
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 1 << ", " << 0 << ", " << 0 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }

        else if(temp->chain == 'D'){
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 1 << ", " << 1 << ", " << 0 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }

        else if(temp->chain == 'E'){
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 1 << ", " << 1 << ", " << 1 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }

        else {
            myfileCol.open("colors.js",std::ios_base::app);
            myfileCol << 1 << ", " << 0.6 << ", " << 0 << ", ";
            myfileCol.close();
            if(colTemp->chain == 'A'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 0 << ", " << 1 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'B'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 0 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'C'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'D'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 0 << ",\n";
                myfileCol.close();
            }else if(colTemp->chain == 'E'){
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 1 << ", " << 1 << ",\n";
                myfileCol.close();
            }else{
                myfileCol.open("colors.js",std::ios_base::app);
                myfileCol << 1 << ", " << 0.6 << ", " << 0 << ",\n";
                myfileCol.close();
            }
        }
        myfileCol.close();

        temp = temp->next;
        temp2 = head;
    }
    myfile.open ("coords.js", std::ios_base::app);
    myfile << "];";
    myfile.close();
    myfileCol.open ("colors.js", std::ios_base::app);
    myfileCol << "];";
    myfileCol.close();
}
