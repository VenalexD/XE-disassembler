/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: opcode.h
*/

#ifndef __a2__C_____opcode__
#define __a2__C_____opcode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class opcode {
public:
    string 	getName(int opCode);
    int 	getFormat(int opCode);
    bool 	getBit(int input, int position);
};
#endif /* defined(__a2__C_____OpCode__) */
