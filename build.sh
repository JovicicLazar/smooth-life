#!/bin/sh

set -xe

g++ -O3 -Wall -Wextra ./src/settings_term.cpp  main.cpp -o smooth_life_term -ljsoncpp -lraylib

g++ smooth_term.cpp -o smooth_life_gpu -lraylib



