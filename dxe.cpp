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
ofstream outSic; //outputs to file
ofstream outLis; //outputs to file

void dxe::openF(string file)
{
        string objF = file + ".obj";    // Adds obj extension to object file
        string symF = file + ".sym";    // Adds sym extension to symbol file
        string sicF = file + ".sic";    // Adds sic extension to source file
        string lisF = file + ".lis";    // Adds lis extension to source file

        inObj.open(objF);

        // If no .obj file is opened, either does NOT exist or NOT readable
        if(!inObj){
                cout << "Unable to open file: " << objF << endl;
                exit(EXIT_FAILURE);
        }

        inSym.open(symF);
        // If no .sym file is opened, either does NOT exist or NOT readable
        if(!inSym){
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
        // Buffer to store line by line of file, each line of the object file will load in
        // as a separate element in the vector.
        string buffer;
        while(inObj.good()){
                getline(inObj, buffer);
                objVector.push_back(buffer);    // Stores .obj file contents into vector
        }

        string buffer2;
        // Similar to before, we load the .sym into a vector, however the .sym contains both the 
        // SYMTAB and the LITTAB, so we split those into their own respective vectors for storage
        while(inSym.good()){
                getline(inSym, buffer2);
                symVector.push_back(buffer2);
        }

        // This sequence will split the contents of the symbol vector into individual vectors
        // that will store the SYMTAB and the LITTAB
        int index = 2;
        for(index = 2; index < symVector.size()-1; index++){
            // will load every line of the symbol file into the SYMTAB vector until it reaches a break
            if(symVector[index][0] != (char)NULL){
                symTable.push_back(symVector[index]);
            }
            else{
                // skips down to the LITTAB 
                index += 3;
                break;
            }
        }
        // will load all LITTAB lines of the symVector into the LITTAB vector
        for(int jndex = index; jndex < symVector.size()-1; jndex++){
            litTable.push_back(symVector[jndex]);
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
                        format2(instructTable, currInst, currRow, currPlace);
                        break;
                case 3:
                        //format 3 is the only reader that can return a value due to the fact
                        //that it handles both format 3 and 4 in the same functions
                        //the nixpbe flags need to kept for the remainder of the program
                        flagReturn = format3(instructTable, currInst, currRow, currPlace);
                        break;
        }
        return (flagReturn * 2);
}

// format 1 accepts the opcode table, the current instruction being evaluated, the row of the object record
// and the place within that record where the instruction was found
void dxe::format1(opcode instTable, int currInst, int CurrRow, int currPlace) { 
    string opName = instTable.getName(currInst);

    //Reference the SYMTAB to check if the currently looked at address matches a symbol in the table
    for (int i = 0; i < symTable.size() - 1; i++) { 
        if (currAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16)) {  //currAddress
            outSic << setw(8) << left << (unsigned int)strtol( symTable[i].substr(0,6).c_str() , NULL, 16);
            outLis << setw(8) << left << (unsigned int)strtol( symTable[i].substr(0,6).c_str() , NULL, 16);
            break;
        }
        // load opcode name into the outstream
        else if (i + 1 >= symTable.size() - 1) {
            outSic << "         " << setw(7) << left << opName;  
            outLis << "         " << setw(7) << left << opName;
        }
    }

    //Reference the LITTAB to check if the currenly looked at address matches a literal in the table
    for (int i = 0; i < litTable.size(); i++) { 
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
    // Loops through symTable vector to check if a symbol name matches current address
    for (int i = 0; i < symTable.size()-1; i++) {
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
    // Loops through litTable to check if a literal matches current address
    for (int i = 0; i < litTable.size(); i++) {
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

    switch (r1) {           // Checks value from register 1 to assign name
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
    switch (r2) {           // Checks value from register 2 to assign name
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

int dxe::format3(opcode instTable, int currInst, int currRow, int currPlace) {
    string opName = instTable.getName(currInst);
    bool nixbpe[6];
    int flagSection = (int)strtol(objVector[currRow].substr(currPlace+1, 2).c_str(), NULL, 16);
    for (int i = 0; i < 6; i++)           // Loops through each flag of nixbpe and assigns value
        nixbpe[i] = instTable.getBit(flagSection, 5-i);

    unsigned int instruction = (unsigned int)strtol(objVector[currRow].substr(currPlace, 2*(3+nixbpe[5])).c_str(), NULL, 16);
    for (int i = 0; i < symTable.size()-1; i++) { // Loops through symTable vector to check if a symbol name matches current address
        if (currAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16)) {
            outSic << setw(8) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16);
            outLis << setw(8) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16);
            break;
        }
        else if (i+1 >= symTable.size()-1) {
            outSic << "        ";
            outLis << "        ";
        }
    }

    for (int i = 0; i < litTable.size(); i++) { // Loops through litTable to check if a literal matches current address
        if (currAddress == (unsigned int)strtol(litTable[i].substr(24, 6).c_str(), NULL, 16)) {
            int literal = (int)strtol(objVector[currRow].substr(currPlace+(2*(3+nixbpe[5])), (unsigned int)strtol(litTable[i].substr(16, 6).c_str(), NULL, 16)).c_str(), NULL, 16);
            outSic << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            outSic << setw(7) << opName << setw(10) << left << (unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16) << endl;
            outSic << setw(14) << right << "LTORG" << endl;
            outLis << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            outLis << setw(7) << left << opName << setw(10) << left << (unsigned int)strtol(litTable[i].substr(8, 6).c_str(), NULL, 16);
            outLis << setfill('0') << right << setw(2*(3+nixbpe[5])) << instruction << setfill(' ') << endl;
            outLis << setfill('0') << setw(4) << right << currAddress << setfill(' ') << "  ";
            outLis << setw(14) << right << "LTORG" << "            " << literal << endl;
            return (3 + ((unsigned int)strtol(litTable[i].substr(16, 6).c_str(), NULL, 16)/2));
        }
    }

    outSic << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
    outLis << (nixbpe[5] ? "+":" ");

    unsigned int targetAddress = 0;
    if (nixbpe[5]) {                    //check for extended format and put displacement field into targetAddress
        targetAddress = (unsigned int)strtol(objVector[currRow].substr(currPlace, 8).c_str(), NULL, 16);
        targetAddress &= 0x000FFFFF;
    }
    else {
        targetAddress = (unsigned int)strtol(objVector[currRow].substr(currPlace, 6).c_str(), NULL, 16);
        targetAddress &= 0x000FFF;
    }

    if (nixbpe[3]) {        //base relative
        targetAddress += baseAddress;
    }
    else if (nixbpe[4]) {   //PC relative
        targetAddress += (currAddress + 3);
    }

    if (opName == "J" || opName == "JEQ" || opName == "JGT" || opName == "JLT" || opName == "JSUB") {
        targetAddress &= (nixbpe[5] ? 0x000FFFFF:0x000FFF);
    }

    if (nixbpe[0] == nixbpe[1]) {   // simple addressing
        outSic << setw(8) << left << opName;
        outLis << setw(8) << left << opName;

        for (int i = 0; i < symTable.size(); i++) { //insert symbol name
            if (targetAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16) && opName != "RSUB") {
                outSic << setw(9) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) + (nixbpe[2] ? ",X":"") << endl;
                outLis << setw(9) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) + (nixbpe[2] ? ",X":"");
                break;
            }
        }
        if (opName == "RSUB") {
            outSic << endl;
            outLis << "         ";
        }
    }
    else if (nixbpe[0]) {   //indirect addressing
        outSic << setw(7) << left << opName << "@";
        outLis << setw(7) << left << opName << "@";
        for (int i = 0; i < symTable.size(); i++) { //insert symbol name
            if (targetAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16) && opName != "RSUB") {
                outSic << setw(9) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) + (nixbpe[2] ? ",X":"") << endl;
                outLis << setw(9) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) + (nixbpe[2] ? ",X":"");
                break;
            }
        }
    }
    else {                  //immediate addressing`
        outSic << setw(7) << left << opName << "#";
        outLis << setw(7) << left << opName << "#";
        if (!nixbpe[5]) {
            outSic << targetAddress << endl;
            outLis << setw(9) << targetAddress;
        }
    }

    if (opName == "LDB") {
        baseAddress = targetAddress;
        for (int i = 0; i < symTable.size(); i++) { //check if symbol name should be inserted
            if (targetAddress == (unsigned int)strtol(symTable[i].substr(8,6).c_str(), NULL, 16)) {
                outSic << setw(10) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) << endl;
                outSic << setw(17) << right << "BASE    " << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) << endl;
                outLis << setw(9) << left << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16);
                outLis << setw(2*(3+nixbpe[5])) << setfill('0') << instruction << setfill(' ') << endl;
                outLis << setfill('0') << setw(4) << right << currAddress << setfill(' ') << "  ";
                outLis << setw(17) << right << "BASE    " << (unsigned int)strtol(symTable[i].substr(0,6).c_str(), NULL, 16) << endl;
                return (3+nixbpe[5]);
            }
        }
    }
    outLis << right << setfill('0') << setw(2*(3+nixbpe[5])) << instruction << setfill(' ') << endl;
    return (3+nixbpe[5]);
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
        // this will fetch the lenghth of the text record so the format finder knows how many times
        // it needs to run for each instruction
        int textLen = (int)strtol( objVector[textRow].substr(7,2).c_str(), NULL, 16 );
        // op codes will always start at least in location 9 on text record
        int curr = 9;
        // this loop will carry the sequence of calling format finder to then call the correct
        // format reader for each instruction
        while(curr < (2* textLen + 9)){
                int size = formatFinder(textRow, curr);
                currAddress += (size/2);
                curr += size;
        }

        //once all formats have been handles we will reference the SYMTAB and the LITTAB using the
        // checkSymTab function
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
                                // if the next value is past the size of SYMTAB then we will finish up the line for that entry
                                if(i+1 < symTable.size()){
                                        outSic << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr)/3 << endl;
                                        outLis << setbase(10) << setw(8) << left << (((unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16))- symAddr)/3 << setbase(16) << endl;
                                        currAddress += (unsigned int)strtol(symTable[i+1].substr(8,6).c_str(), NULL,16) - symAddr;
                                }
                                // if not then we continue on and update the address 
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
