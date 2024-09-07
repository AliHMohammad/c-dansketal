#!/bin/bash

set -e

gcc -Wall -I./src/include -I./src/ui -o ./build/file ./src/*.c ./src/ui/*.c
./build/file
