#!/bin/bash

# Get all the .c files in the current directory.
c_files=$(ls *.c)

# Compile the .c files to object files.
for c_file in $c_files; do
    gcc -c -fPIC $c_file
done

# Create the dynamic library.
gcc -shared -o liball.so *.o

