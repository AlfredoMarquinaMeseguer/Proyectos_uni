#!/bin/bash


flex $1.l
gcc lex.yy.c main.c -lfl -o $1
./$1
