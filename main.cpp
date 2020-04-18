/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: main.cpp
*/

#include "dxe.h"
using namespace std;

int main(int argc, char *argv[])
{
        // Given two arguments were given (executable program and file to be read)
        if(argc == 2)
        {
            // Instantiates XED form dxe class
            dxe XED;
            XED.openF(argv[1]); // Calls open function with command line argument
            XED.recordFinder();
        }

        else
        {
                cout << "Usage: " << argv[0] << " <filename>" << endl;  // Shows the correct usage of the program and arguments
        }
        
        return 0;
}
