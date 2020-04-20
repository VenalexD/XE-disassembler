/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: dxe.h
*/

#ifndef DXE_H
#define DXE_H

#include<iostream>
#include <iomanip>
#include <vector>
#include "opcode.h"

class dxe
{
    public:
        void openF(string file);
        void recordFinder();

    private:
        void storeVector();
        void opCodeMap();
        void headerReader(int);
        void textReader(int);
        void checkSymTab();
        void modReader(int);
        void endReader(int);
        int formatFinder(int,int);
        void format1(opcode,int,int,int);
        void format2(opcode,int,int,int);
        int format3(opcode,int,int,int);

        vector<string> objVector; //where we load each record
        vector<string> symVector; //where we load each symbol

        vector<string> symTable;    // Where we load each line of sym table
        vector<string> litTable;    // Where we load each line of lit table
          
        unsigned int programLength;
        unsigned int currAddress;
        unsigned int baseAddress;

};

#endif
