#!/bin/sh

set -xe

g++ -O3 -Wall -Wextra ./src/settings_term.cpp  smooth_life_terminal.cpp -o smooth_life_terminal -ljsoncpp

g++ -O3 -Wall -Wextra ./src/settings_gpu.cpp smooth_life_gpu.cpp -o smooth_life_gpu -lraylib -ljsoncpp



