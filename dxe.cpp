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
        // Given two arguments were given (executable program and file to be read)
        if(argc == 2)
        {
                ifstream inFile;
                string file = argv[1];  // Assign variable name "file" to second argument (file to be read)
                string objF = file + ".obj";    // Adds obj extension to object file
                string symF = file + ".sym";    // Adds sym extension to symbol file
                string sicF = file + ".sic";    // Adds sic extension to source file

                // Creates and opens source file
                ofstream outFile(sicF);

                

                inFile.open(objF);
                outFile << "test";
                // If no file is opened, either does NOT exist or NOT readable
                if(!inFile)
                {
                        cout << "Unable to open file: " << file << endl;
                        return -1;      // Exits program
                }
                outFile.close();
                inFile.close();
        }

        // Given two arguments were NOT given (executable program and file to be read)
        else
        {
                cout << "Usage: " << argv[0] << " <filename>" << endl;  // Shows the correct usage of the program and arguments
        }
        
        return 0;
}
