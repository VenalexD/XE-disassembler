/*
Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: dxe.c
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
        if(argc == 2)
        {
                FILE *file = fopen(argv[1], "r");

                fclose(file);
        }

        else
        {
                printf("usage: %s <filename>\n", argv[0]);
        }
        return 0;
}