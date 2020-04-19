/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: opcode.cpp
*/

#include "opcode.h"
#define SIZE 59

//Creates a structure of opCodes with a format of {NAME, OPCODE, FORMAT of operation}
struct code {
    string name;
    int format; //format 3 is actually format 3/4,  but this will be decided in the main program
    int opCode;
};

const struct code instTable [] = {				//structure of usable commands
    {"ADD", 3, 0x18 },  {"ADDF", 3, 0x58},   {"ADDR", 2, 0x90},   {"AND", 3, 0x40},  {"CLEAR", 2, 0xB4},
    {"COMP", 3, 0x28}, {"COMPF", 3, 0x88},  {"COMPR", 2, 0xA0},  {"DIV", 3, 0x24},  {"DIVF", 3, 0x64},
    {"DIVR", 2, 0x9C}, {"FIX", 1, 0xC4},    {"FLOAT", 1, 0xC0},  {"HIO", 1, 0xF4},  {"J", 3, 0x3C},
    {"JEQ", 3, 0x30},  {"JGT", 3, 0x34},    {"JLT", 3, 0x38},    {"JSUB", 3, 0x48}, {"LDA", 3, 0x00},
    {"LDB", 3, 0x68},  {"LDCH", 3, 0x50},   {"LDF", 3, 0x70},    {"LDL", 3, 0x08},  {"LDS", 3, 0x6C},
    {"LDT", 3, 0x74},  {"LDX", 3, 0x04},    {"LPS", 3, 0xD0},    {"MUL", 3, 0x20},  {"MULF", 3, 0x60},
    {"MULR", 2, 0x98}, {"NORM", 1, 0xC8},   {"OR", 3, 0x44},     {"RD", 3, 0xD8},   {"RMO", 2, 0xAC},
    {"RSUB", 3, 0x4C}, {"SHIFTL", 2, 0xA4}, {"SHIFTR", 2, 0xA8}, {"SIO", 1, 0xF0},  {"SSK", 3, 0xEC},
    {"STA", 3, 0x0C},  {"STB", 3, 0x78},    {"STCH", 3, 0x54},   {"STF", 3, 0x80},  {"STI", 3, 0xD4},
    {"STL", 3, 0x14},  {"STS", 3, 0x7C},    {"STSW", 3, 0xE8},   {"STT", 3, 0x84},  {"STX", 3, 0x10},
    {"SUB", 3, 0x1C},  {"SUBF", 3, 0x5C},   {"SUBR", 2, 0x94},   {"SVC", 2, 0xB0},  {"TD", 3, 0xE0},
    {"TIO", 1, 0xF8},  {"TIX", 3, 0x2C},    {"TIXR", 2, 0xB8},   {"WD", 3, 0xDC}
};

string opcode::getName(int opCode) {
    for (int i = 0; i < SIZE; i++)
        if (instTable[i].opCode == opCode)
            return instTable[i].name;										//05    0000 0101
    int newOpCode = opCode & 0xFC;      	//allows us to get the NAME       FC	1111 1100
    return getName(newOpCode);											//00	0000 0000   => LDA, Format 3
}

int opcode::getFormat(int opCode) {											//05    0000 0101
    opCode = opCode & 0xFC;      			//allows us to get the FORMAT     FC	1111 1100
    for (int i = 0; i < SIZE; i++)										    //04	0000 0100   => LDX, Format 3
        if (instTable[i].opCode == opCode)
            return instTable[i].format;
    return 0;
}

bool opcode::getBit(int input, int position) {		//fills nixbpe for format 3/4 in Format 3 function
    return ((input >> position) & 1);
}

