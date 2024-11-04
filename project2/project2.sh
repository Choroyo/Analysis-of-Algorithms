#!/bin/bash
# Script to compile and run project

# Compile the C++ program
g++ project2.cpp -o project2


# Execute the program with the control file as argument
./project2 "$1"