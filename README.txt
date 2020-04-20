Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
Users: cssc1967, cssc1923, cssc1921, cssc1964
Class: CS 530, Spring 2020
Assignment 2, XE Dissasembler
Filename: README.txt

*********************************************************************************************

File manifest:
dxe.cpp, opcode.cpp, main.cpp >>> Source code
dxe.h, opcode.h >>> Header files
Makefile >>> Tool for compiling program

After compiling using makefile:
dxe >>> Executable file

*********************************************************************************************

Compile instructions:
Inside ~/a2 folder, type 'make' command and makefile will compile the code automatically.

*********************************************************************************************

Operating instructions:
Disassembler program for the XE variant of the SIC/XE family of machines.

After compiling code with 'make' command an executable file named "dxe" will be created.
Type "dxe" followed by filename and the program will run.
Usage:
dxe <filename>

After the program is executed, <filename>.sym and <filename>.obj are opened and read, then  two files are created: <filename>.sic and <filename>.lis
