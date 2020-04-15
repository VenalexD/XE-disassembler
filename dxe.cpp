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
<<<<<<< HEAD
#include <map>
#include "dxe.h"
=======
//#include <map>
>>>>>>> 0377da2ab0b01cdb721bb289551d909a3ad403a1

ifstream inObj;
ifstream inSym;
ofstream outSic;
ofstream outLis;

void dxe::openF(char *file)
{
        string objF = *file + ".obj";    // Adds obj extension to object file
        string symF = *file + ".sym";    // Adds sym extension to symbol file
        string sicF = *file + ".sic";    // Adds sic extension to source file
        string lisF = *file + ".lis";    // Adds lis extension to source file

        inObj.open(objF);
        // If no .obj file is opened, either does NOT exist or NOT readable
        if(!inObj)
        {
                cout << "Unable to open file: " << objF << endl;
                exit(EXIT_FAILURE);
        }

<<<<<<< HEAD
        inSym.open(symF);
        // If no .sym file is opened, either does NOT exist or NOT readable
        if(!inSym)
=======
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
>>>>>>> 0377da2ab0b01cdb721bb289551d909a3ad403a1
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
                                //headerReader(i);
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