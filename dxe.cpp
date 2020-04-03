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
#include <math.h>

using namespace std;

int hexToDec(unsigned char hex[])
{
        int hexInt[6];  // Holds int values of hex
        int sum = 0;    // Holds sum of hex values
        for(int i=0; i<6; i++)
        {
                if(hex[i] >= 48 && hex[i] <= 57)
                {
                        hexInt[i] = (int) hex[i] - 48;  // Converts char to int value and subtracts 48
                }

                else if(hex[i] >= 65 && hex[i] <= 70)
                {
                        hexInt[i] = (int) hex[i] - 55;  // Converts char to int value and subtracts 55
                }

                else
                {
                        cout << "Invalid Hex value found" << endl;
                        exit(1);      // Exits program
                }
                
                sum += pow(16, i)*hexInt[i];
        }

        return sum;
}

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

                inFile.open(objF);
                // If no file is opened, either does NOT exist or NOT readable
                if(!inFile)
                {
                        cout << "Unable to open file: " << file << endl;
                        return -1;      // Exits program
                }

                // Creates and opens source file
                ofstream outFile(sicF);
                char c; // Placeholder for character being read
                inFile.get(c);  // Skips first character 'H'
                // Loops through 6 characters of program name
                for(int i=0; i<6; i++)
                {
                        inFile.get(c);  // Gets character from input file
                        outFile << c;   // Writes each charatcer to output file
                }

                unsigned char x[6];       // Int array to hold hex values
                // Loops through 6 hex digits of object program starting address
                for(int j=0; j<6; j++)
                {
                        inFile.get(c);
                        x[j] = c;
                }

                outFile << "   START   " << hexToDec(x);

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
