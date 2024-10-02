#!/usr/bin/bash

mkdir -p build
g++ experiments/sample.cpp -o build/sample -g -Werror
