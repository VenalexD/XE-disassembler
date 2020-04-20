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

        string buffer2;
        while(inSym.good())
        {
                getline(inSym, buffer2);
                getline(inSym, buffer2);
                getline(inSym, buffer2);
                while(buffer2.length() != 0)
                {
                        symTable.push_back(buffer2);    // Stores symbol table lines into vector//
                        getline(inSym, buffer2);
                }


        }

        while(inSym.good())
        {
                getline(inSym, buffer2);
                getline(inSym, buffer2);
                getline(inSym, buffer2);
                while(buffer2.length() != 0)
                {
                        litTable.push_back(buffer2);    // Stores symbol table lines into vector
                        getline(inSym, buffer2);
                }      
        }
}

//Base on the first value returned in each row of the objVector the record finder will call
//the corresponding function based on which kind of record it is.
void dxe::recordFinder()
{
        for (int i = 0; i < objVector.size(); i++){
                switch (objVector[i][0]){
                        case 'H': 
                                headerReader(i);
                                break;
                        case 'T': 
                                textReader(i);
                                break;
                        case 'M':
                                modReader(i);
                                break;
                        case 'E':
                                endReader(i);
                                break;
                        default:
                                break;
                }
        
        }
}

int dxe::formatFinder(int currRow, int currPlace){
        //instatiate a new instruction table
        opcode instructTable = *new opcode;
        int flagReturn;
        //pull the first two bytes from the currPlace row and the currPlace place.
        int currInst = (int)strtol(objVector[currRow].substr(currPlace,2).c_str(),NULL,16);
        
        //call the .getFormat table from the instruction table class to fetch the format of the instruction
        int instFormat = instructTable.getFormat(currInst);
        
        //output the instruction address to the .lis file
        outLis << setfill('0') << setw(4) << right << currAddress << setfill(' ') << " ";

        //this switch case will pick the right format disassembler
        switch(instFormat) {
                case 1:
                        format1(instructTable, currInst, currRow, currPlace);
                        break;
                case 2: 
                        //format2(instTable, currInst, currRow, currPlace);
                        break;
                case 3:
                        //flagReturn = format3(instTable, currInst, currRow, currPlace);
                        break;
        }
        return (flagReturn * 2);
}

void dxe::format1(opcode instTable, int currInst, int CurrRow, int currPlace) { 
    string opName = instTable.getName(currInst);

    for (int i = 0; i < symTable.size() - 1; i++) { //check if symbol name should be inserted
        if (currAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16)) {  //currAddress
            outSic << setw(8) << left << (unsigned int)strtol( symTable[i].substr(0,6).c_str() , NULL, 16);
            outLis << setw(8) << left << (unsigned int)strtol( symTable[i].substr(0,6).c_str() , NULL, 16);
            break;
        }
        else if (i + 1 >= symTable.size() - 1) {
            outSic << "         " << setw(7) << left << opName;  //not sure on opName
            outLis << "         " << setw(7) << left << opName;
        }
    }

    for (int i = 0; i < litTable.size(); i++) { //check if literal should be inserted
        if (currAddress == (unsigned int)strtol(litTable[i].substr(24, 6).c_str(), NULL, 16)) {
            outSic << setw(10) << left << (unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16) << endl;
            outSic << setw(14) << right << "LTORG" << endl;
            outLis << setw(10) << left << (unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16) << endl;
            outLis << setw(14) << right << "LTORG" << endl;
            return;
        }
    }
}


void dxe::format2(opcode instTable, int currInst, int currRow, int currPlace) {
    string opName = instTable.getName(currInst);

    for (int i = 0; i < symTable.size()-1; i++) { //check if symbol name should be inserted
        if (currAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16)) {
            outSic << setw(8) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16);
            outLis << setw(8) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16);
            break;
        }
        else if (i+1 >= symTable.size()-1) {
            outSic << "         " << setw(7) << left << opName;
            outLis << "         " << setw(7) << left << opName;
        }
    }

    for (int i = 0; i < litTable.size(); i++) { //check if literal should be inserted
        if (currAddress == (unsigned int)strtol(litTable[i].substr(24, 6).c_str(), NULL, 16)) {
            outSic << setw(10) << left <<(unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16)<< endl;
            outSic << setw(14) << right << "LTORG" << endl;
            outLis << setw(10) << left << (unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16) << endl;
            outLis << setw(14) << right << "LTORG" << endl;
            return;
        }
    }
    int r1 = (int)strtol(objVector[currRow].substr(currPlace+2, 1).c_str(), NULL, 16);
    int r2 = (int)strtol(objVector[currRow].substr(currPlace+3, 1).c_str(), NULL, 16);

    switch (r1) {           //output register name for first register operand
        case 0:
        	outSic << "A,";
            outLis << "A,";
            break;
        case 1:
            outSic << "X,";
            outLis << "X,";
            break;
        case 2:
            outSic << "L,";
            outLis << "L,";
            break;
        case 3:
            outSic << "B,";
            outLis << "B,";
            break;
        case 4:
            outSic << "S,";
            outLis << "S,";
            break;
        case 5:
            outSic << "T,";
            outLis << "T,";
            break;
        case 6:
            outSic << "F,";
            outLis << "F,";
            break;
        default:
            break;
    }
    switch (r2) {           //output register name for 2nd operand
        case 0:
            outSic << "A" << endl;
            outLis << "A" << endl;
            break;
        case 1:
            outSic << "X" << endl;
            outLis << "X" << endl;
            break;
        case 2:
            outSic << "L" << endl;
            outLis << "L" << endl;
            break;
        case 3:
            outSic << "B" << endl;
            outLis << "B" << endl;
            break;
        case 4:
            outSic << "S" << endl;
            outLis << "S" << endl;
            break;
        case 5:
            outSic << "T" << endl;
            outLis << "T" << endl;
            break;
        case 6:
            outSic << "F" << endl;
            outLis << "F" << endl;
            break;
        default:
            break;
    }
}


void dxe::headerReader(int textRow)
{
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

void dxe::textReader(int textRow){
        int textLen = (int)strtol( objVector[textRow].substr(7,2).c_str(), NULL, 16 );
        // op codes will always start at least in location 9 on text record
        int curr = 9;
        while(curr < (2* textLen + 9)){
                int size = formatFinder(textRow, curr);
                currAddress += (size/2);
                curr += size;
        }

        checkSymTab();
}

void dxe::checkSymTab(){
        for (int i =0; i < symTable.size(); i++){
                //fetch the name of the ith symbol in the Symbol Table
                string symName = symTable[i].substr(0,6);
                //fetch the address of the ith symbol in the Symbol Table
                unsigned int symAddr = (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16);
                //check if the currPlace address is the same as a symbol in the Symbol Table
                if(currAddress <= symAddr)
                        outLis << setfill('0') << setw(4) << right << currAddress << setfill(' ') << "  ";
                        if ((currAddress % 3)){
                                outSic << setw(8) << left << symName << " RESW    ";
                                outLis << setw(8) << left << symName << " RESW    ";

                                if(i+1 < symTable.size()){
                                        outSic << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr)/3 << endl;
                                        outLis << setbase(10) << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr)/3 << setbase(16) << endl;
                                        currAddress += (unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16) - symAddr;
                                }
                                else{
                                        outSic << setw(8) << left << (programLength - symAddr)/3 << endl;
                                        outLis << setbase(10) << setw(8) << left << (programLength - symAddr)/3 << setbase(16) << endl;
                                        currAddress += (programLength - symAddr);
                                }
                        }
                        else{
                                outSic << setw(8) << left << symName << " RESB    ";
                                outLis << setw(8) << left << symName << " RESB    ";
                                if( i+1 < symTable.size()){
                                        outSic << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr) << setbase(16) << endl;
                                        outLis << setbase(10) << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr) << setbase(16) << endl;
                                        currAddress += ((((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr))/3;
                                }
                                else{
                                        outSic << setw(8) << left << (programLength - symAddr)/3 << endl;
                                        outLis << setbase(10) << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr) << setbase(16) << endl;
                                        currAddress += (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr) / 3;
                                }
                        }
        }
}
void dxe::modReader(int textRow){     //M XXXXXX YY

	int i = 0;
	unsigned int addressT = 0;
               //finds the first text record
	while (objVector[i][0] != 'T') {   
	       i++;
	}
	addressT = (unsigned int)strtol(objVector[i].substr(1, 6).c_str(), NULL, 16);  //store text start address at addressT as a long

		// Grab the 6 chars after the 'M' which is the starting address of the field to be modified
	unsigned int modificationAddress = ( unsigned int)strtol( objVector[textRow].substr(1,6).c_str(), NULL, 16);

		//takes in the length of the address to be modified
        int modificationLength = (int)strtol(objVector[textRow].substr(7, 2).c_str(), NULL, 16);


		//find text record that contains the address to modify
        while (addressT < modificationLength) {
	       addressT += (unsigned int)strtol(objVector[i].substr(7, 2).c_str(), NULL, 16);
	       i++;
        }
	    
	i--;
	addressT -= (unsigned int)strtol(objVector[i].substr(7, 2).c_str(), NULL, 16);
	int position = 2 * (modificationAddress - addressT) + 10;
	objVector[i][position] += programLength;
}

void dxe::endReader(int textRow) {
    // sets end address equal to our object vector with 16 length
    unsigned int eAddress = (unsigned int)strtol(objVector[textRow].substr(1, 6).c_str(), NULL, 16);
    //check the symbol value vector table for the address of the front instruction
    for (int i = 0; i < symTable.size(); i++) 
        if (eAddress == (unsigned int)strtol(symTable[i].substr(8, 6).c_str(), NULL, 16)) {
            //makes room in the Sic stream for the next packet on information
            outSic << "         " << setw(8) << left << "END" << symTable[i].substr(0,6) << endl;
            //makes room in the Lis stream for the next packet on information
            outLis << "               " << setw(8) << left << "END" << symTable[i].substr(0,6) << endl;
            break;
        }
}