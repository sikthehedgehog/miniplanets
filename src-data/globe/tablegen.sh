#!/bin/sh
gcc -std=c99 -o tablegen tablegen.c -lm
gcc -std=c99 -o tablegen2 tablegen2.c -lm
./tablegen
./tablegen2
