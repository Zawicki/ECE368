#!/bin/bash

echo "Compiling Program"

gcc -Werror -Wbad-function-cast -Wall -Wshadow -O3 reroot.c -o proj4
