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
//#include <map>

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

/*
void buildObjMap(map<int, string> &obj_map){

    obj_map[0x18]= "ADD3";
    obj_map[0x58]= "ADDF3";
    obj_map[0x90]= "ADDR2";
    obj_map[0x40]= "AND3";
    obj_map[0xB4]= "CLEAR2";
    obj_map[0x28]= "COMP3";
    obj_map.insert(pair<int, string>(0x88,"COMPF3"));
    obj_map.insert(pair<int, string>(0xA0,"COMPR2"));
    obj_map.insert(pair<int, string>(0x24,"DIV3"));
    obj_map.insert(pair<int, string>(0x64,"DIVF3"));
    obj_map.insert(pair<int, string>(0x9C,"DIVR2"));
    obj_map.insert(pair<int, string>(0xC4,"FIX1"));
    obj_map.insert(pair<int, string>(0xC0,"FLOAT1"));
    obj_map.insert(pair<int, string>(0xF4,"HIO1"));
    obj_map.insert(pair<int, string>(0x3C,"J3"));
    obj_map.insert(pair<int, string>(0x30,"JEQ3"));
    obj_map.insert(pair<int, string>(0x34,"JGT3"));
    obj_map.insert(pair<int, string>(0x38,"JLT3"));
    obj_map.insert(pair<int, string>(0x48,"JSUB3"));
    obj_map.insert(pair<int, string>(0x00,"LDA3"));
    obj_map.insert(pair<int, string>(0x68,"LDB3"));
    obj_map.insert(pair<int, string>(0x50,"LDCH3"));
    obj_map.insert(pair<int, string>(0x70,"LDF3"));
    obj_map.insert(pair<int, string>(0x8,"LDL3"));
    obj_map.insert(pair<int, string>(0x6C,"LDS3"));
    obj_map.insert(pair<int, string>(0x74,"LDT3"));
    obj_map.insert(pair<int, string>(0x04,"LDX3"));
    obj_map.insert(pair<int, string>(0xD0,"LPS3"));
    obj_map.insert(pair<int, string>(0x20,"MUL3"));
    obj_map.insert(pair<int, string>(0x60,"MULF3"));
    obj_map.insert(pair<int, string>(0x98,"MULR2"));
    obj_map.insert(pair<int, string>(0xC8,"NORM1"));
    obj_map.insert(pair<int, string>(0x44,"OR3"));
    obj_map.insert(pair<int, string>(0xD8,"RD3"));
    obj_map.insert(pair<int, string>(0xAC,"RMO2"));
    obj_map.insert(pair<int, string>(0x4C,"RSUB3"));
    obj_map.insert(pair<int, string>(0xA4,"SHIFTL2"));
    obj_map.insert(pair<int, string>(0xA8,"SHIFTR2"));
    obj_map.insert(pair<int, string>(0xF0,"SIO1"));
    obj_map.insert(pair<int, string>(0xEC,"SSK3"));
    obj_map.insert(pair<int, string>(0x0C,"STA3"));
    obj_map.insert(pair<int, string>(0x78,"STB3"));
    obj_map.insert(pair<int, string>(0x54,"STCH3"));
    obj_map.insert(pair<int, string>(0x80,"STF3"));
    obj_map.insert(pair<int, string>(0xD4,"STI3"));
    obj_map.insert(pair<int, string>(0x14,"STL3"));
    obj_map.insert(pair<int, string>(0x7C,"STS3"));
    obj_map.insert(pair<int, string>(0xE8,"STSW3"));
    obj_map.insert(pair<int, string>(0x84,"STT3"));
    obj_map.insert(pair<int, string>(0x10,"STX3"));
    obj_map.insert(pair<int, string>(0x1C,"SUB3"));
    obj_map.insert(pair<int, string>(0x5C,"SUBF3"));
    obj_map.insert(pair<int, string>(0x94,"SUBR2"));
    obj_map.insert(pair<int, string>(0xB0,"SVC2"));
    obj_map.insert(pair<int, string>(0xE0,"TD3"));
    obj_map.insert(pair<int, string>(0xF8,"TIO1"));
    obj_map.insert(pair<int, string>(0x2C,"TIX3"));
    obj_map.insert(pair<int, string>(0xB8,"TIXR2"));
    obj_map.insert(pair<int, string>(0xDC,"WD3"));
}
*/

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
