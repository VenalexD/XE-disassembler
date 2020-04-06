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
#include <map>

using namespace std;

// Function to create map of opcodes and instructions
void buildObjMap(map<int, string> &obj_map)
{
    obj_map.insert(pair<int, string>(0x18, "ADD"));
    obj_map.insert(pair<int, string>(0x58, "ADDF"));
    obj_map.insert(pair<int, string>(0x90, "ADDR"));
    obj_map.insert(pair<int, string>(0x40, "AND"));
    obj_map.insert(pair<int, string>(0xB4, "CLEAR2"));
    obj_map.insert(pair<int, string>(0x28, "COMP"));
    obj_map.insert(pair<int, string>(0x88, "COMPF"));
    obj_map.insert(pair<int, string>(0xA0, "COMPR"));
    obj_map.insert(pair<int, string>(0x24, "DIV"));
    obj_map.insert(pair<int, string>(0x64, "DIVF"));
    obj_map.insert(pair<int, string>(0x9C, "DIVR"));
    obj_map.insert(pair<int, string>(0xC4, "FIX"));
    obj_map.insert(pair<int, string>(0xC0, "FLOAT"));
    obj_map.insert(pair<int, string>(0xF4, "HIO"));
    obj_map.insert(pair<int, string>(0x3C, "J"));
    obj_map.insert(pair<int, string>(0x30, "JEQ"));
    obj_map.insert(pair<int, string>(0x34, "JGT"));
    obj_map.insert(pair<int, string>(0x38, "JLT"));
    obj_map.insert(pair<int, string>(0x48, "JSUB"));
    obj_map.insert(pair<int, string>(0x00, "LDA"));
    obj_map.insert(pair<int, string>(0x68, "LDB"));
    obj_map.insert(pair<int, string>(0x50, "LDCH"));
    obj_map.insert(pair<int, string>(0x70, "LDF"));
    obj_map.insert(pair<int, string>(0x08, "LDL"));
    obj_map.insert(pair<int, string>(0x6C, "LDS"));
    obj_map.insert(pair<int, string>(0x74, "LDT"));
    obj_map.insert(pair<int, string>(0x04, "LDX"));
    obj_map.insert(pair<int, string>(0xD0, "LPS"));
    obj_map.insert(pair<int, string>(0x20, "MUL"));
    obj_map.insert(pair<int, string>(0x60, "MULF"));
    obj_map.insert(pair<int, string>(0x98, "MULR"));
    obj_map.insert(pair<int, string>(0xC8, "NORM"));
    obj_map.insert(pair<int, string>(0x44, "OR"));
    obj_map.insert(pair<int, string>(0xD8, "RD"));
    obj_map.insert(pair<int, string>(0xAC, "RMO"));
    obj_map.insert(pair<int, string>(0x4C, "RSUB"));
    obj_map.insert(pair<int, string>(0xA4, "SHIFTL"));
    obj_map.insert(pair<int, string>(0xA8, "SHIFTR"));
    obj_map.insert(pair<int, string>(0xF0, "SIO"));
    obj_map.insert(pair<int, string>(0xEC, "SSK"));
    obj_map.insert(pair<int, string>(0x0C, "STA"));
    obj_map.insert(pair<int, string>(0x78, "STB"));
    obj_map.insert(pair<int, string>(0x54, "STCH"));
    obj_map.insert(pair<int, string>(0x80, "STF"));
    obj_map.insert(pair<int, string>(0xD4, "STI"));
    obj_map.insert(pair<int, string>(0x14, "STL"));
    obj_map.insert(pair<int, string>(0x7C, "STS"));
    obj_map.insert(pair<int, string>(0xE8, "STSW"));
    obj_map.insert(pair<int, string>(0x84, "STT"));
    obj_map.insert(pair<int, string>(0x10, "STX"));
    obj_map.insert(pair<int, string>(0x1C, "SUB"));
    obj_map.insert(pair<int, string>(0x5C, "SUBF"));
    obj_map.insert(pair<int, string>(0x94, "SUBR"));
    obj_map.insert(pair<int, string>(0xB0, "SVC"));
    obj_map.insert(pair<int, string>(0xE0, "TD"));
    obj_map.insert(pair<int, string>(0xF8, "TIO"));
    obj_map.insert(pair<int, string>(0x2C, "TIX"));
    obj_map.insert(pair<int, string>(0xB8, "TIXR"));
    obj_map.insert(pair<int, string>(0xDC, "WD"));
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

                // Creates map of opcodes and instructions
                map<int, string> opCodes;
                buildObjMap(opCodes);

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

                string hex;     // String to hold hex value
                int hexDec;     // Int to hold decimal value of hex
                // Loops through 6 hex digits of object program starting address
                for(int j=0; j<6; j++)
                {
                        inFile.get(c);
                        hex.insert(hex.end(), c); // Inserts hex char to string
                }
                
                hexDec = stoi(hex, 0, 16);       // Converts hex value to decimal (Starting addres)

                outFile << "   START   " << hexDec;     // Writes starting address to output file

                hex = "";       // Clears hex string to be reused
                // Loops through next 6 hex digits (Length of program)
                for(int k=0; k<6; k++)
                {
                        inFile.get(c);
                        hex.insert(hex.end(), c); // Inserts hex char to string
                }

                hexDec = stoi(hex, 0, 16);      // Converts hex value to decimal (Lenght of program)



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
