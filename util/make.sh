#!/usr/bin/bash

mkdir -p build
mkdir -p build/debug
g++ src/main.cpp -o build/logic_solver -std=c++23 -I./src -g -Werror -Wall
