#!/bin/sh
gcc -std=c99 -o tablegen tablegen.c -lm
./tablegen
