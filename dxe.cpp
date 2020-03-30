/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: dxe.cpp
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
        if(argc == 2)
        {
                ifstream inFile;
                string file = argv[1];
                inFile.open(file);
                
                if(!inFile)
                {
                        cout << "Unable to open file: " << file << endl;
                        return -1;
                }

                inFile.close();
        }

        else
        {
                cout << "Usage: " << argv[0] << " <filename>" << endl;
        }
        
        return 0;
}
