/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: opcode.cpp
*/

#include "opcode.h"

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
