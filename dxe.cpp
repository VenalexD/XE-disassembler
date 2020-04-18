/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: dxe.cpp
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "dxe.h"

ifstream inObj;
ifstream inSym;
ofstream outSic;
ofstream outLis;

void dxe::openF(string file)
{
        string objF = file + ".obj";    // Adds obj extension to object file
        string symF = file + ".sym";    // Adds sym extension to symbol file
        string sicF = file + ".sic";    // Adds sic extension to source file
        string lisF = file + ".lis";    // Adds lis extension to source file

        inObj.open(objF);
        // If no .obj file is opened, either does NOT exist or NOT readable
        if(!inObj)
        {
                cout << "Unable to open file: " << objF << endl;
                exit(EXIT_FAILURE);
        }

        inSym.open(symF);
        // If no .sym file is opened, either does NOT exist or NOT readable
        if(!inSym)
        {
                cout << "Unable to open file: " << symF << endl;
                exit(EXIT_FAILURE);
        }

        // Creates and opens .sic file
        outSic.open(sicF);
        // Creates and opens .lis file
        outLis.open(lisF);

        // Calls function to store file contents into vector
        storeVector();

        // Closes .obj and .sym files
        inObj.close();
        inSym.close();
}

void dxe::storeVector()
{       
        // Buffer to store line by line of file
        string buffer;
        while(inObj.good())
        {
                getline(inObj, buffer);
                objVector.push_back(buffer);    // Stores .obj file contents into vector
        }

        while(inSym.good())
        {
                getline(inSym, buffer);
                symVector.push_back(buffer);    // Stores .sym file contents into vector
        }
}

void dxe::opCodeMap()
{
        // Creates map of opcodes and instructions
        map<int, string> opCodes;
        buildObjMap(opCodes);
}


void dxe::recordFinder(){
        for (int i = 0; i < objVector.size(); i++){
                switch (objVector[i][0]){
                        case 'H': 
                                headerReader(i);
                                break;
                        case 'T': 
                                //textReader(i);
                                break;
                        case 'M':
                                //modReader(i);
                                break;
                        case 'E':
                                //endReader(i);
                                break;
                        default:
                                break;
                }
        
        }
}

void dxe::headerReader(int textRow){
}
        //in the header, grab the first 6 characters after the 'H' to get the program name
        string programName = objVector[textRow].substr(1,6);
        stringstream temp;

        //grab the 6 characters in the header record which hold the start address of the program
        unsigned int startAddr = currAddress = (unsigned int)strtol(objVector[textRow].substr(7,6).c_str(), NULL, 16);
        //grab the 6 characters in the header record which hold the length of the program
        programLength = (unsigned int)strtol(objVector[textRow].substr(13, 6).c_str(), NULL, 16);

        temp << startAddr;
        string addr = temp.str();

        //we write out to the .sic stream the program name and the starting address
        outSic << setw(9) << left << programName << "START   " << addr << endl;
        //we write out to the .lis file but this time we include addresses and we set the base to Hex
        outLis << setbase(16) << uppercase << setw(4) << setfill('0') << currAddress << setfill(' ') << "  ";
        outLis << setw(9) << left << programName << "START  " << addr <<endl;
}
