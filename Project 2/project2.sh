#!/bin/bash
# Script to compile and run project

# Compile the C++ program
g++ -o project2 project2.cpp

# Execute the program with the control file as argument
./project2 "$1"