#!/bin/bash

echo "Compiling Program"

gcc -Werror -Wbad-function-cast -Wall -Wshadow -O3 packing.c -o proj3
