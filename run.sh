#!/bin/bash

set -e

gcc -Wall -I./src/include  -o ./build/file.exe ./src/*.c 
./build/file.exe
