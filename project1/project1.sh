#!/bin/bash

# Check if the input file is provided as an argument
if [ -z "$1" ]; then
    echo "No input file provided."
    exit 1
fi

# Assign the argument (input file) to a variable
input_file="$1"

# Run the Python script, passing the input file as an argument
python3 project1.py "$input_file"
