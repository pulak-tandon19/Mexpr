#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "--- Generating Lexer ---"
lex Parser.l

echo "--- Compiling lex.yy.c ---"
g++ -g -c lex.yy.c -o lex.yy.o

echo "--- Compiling ExpressionParser.c ---"
g++ -g -c ExpressionParser.c -o ExpressionParser.o

echo "--- Compiling EnumConverter.cpp ---"
g++ -g -c EnumConverter.cpp -o EnumConverter.o

echo "--- Linking executable ---"
g++ -g lex.yy.o ExpressionParser.o EnumConverter.o -o exe -lfl

echo "--- Build Successful! Run with ./exe ---"