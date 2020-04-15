/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: dxe.h
*/

#include<iostream>
#include <vector>
#include "opcode.h"

class dxe
{
    public:
        void openF(char *file);

    private:
        void storeVector();
        void opCodeMap();
        vector<string> objVector;
        vector<string> symVector;

};
