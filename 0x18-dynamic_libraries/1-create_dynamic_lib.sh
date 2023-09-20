#!/bin/bash
gcc *.c -c -fPIC
# Create the dynamic library.
gcc *.o -shared -o liball.so
