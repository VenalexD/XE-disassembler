###########################################################
#
# Authors: Alex Gonzalez, Juan Pina-Sanz, Mikhail Mineev, Mark Khoury
# Users: cssc1967, cssc1923, cssc1921, cssc1964
# Class: CS 530, Spring 2020
# Assignment 2, XE Dissasembler
# Filename: Makefile
#
###########################################################
EXEC = dxe
FILES = main.cpp dxe.cpp opcode.cpp
CC = g++
LFLAGS = -lm -o
CFLAGS = -lm -o

$(EXEC):$(FILES)
	$(CC) $(FILES) $(LFLAGS) $(EXEC) 

clean:
	rm -f *.o $(EXEC)

.PHONY: all dxe clean
#######################[ EOF: Makefile ]###################
