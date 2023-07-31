# smooth-life
The Game of Life is a cellular automaton, a zero-player game devised by John Conway in 1970. It operates on a grid of cells, where each cell can be in one of two states: alive or dead. The state of each cell evolves over time based on a set of rules.

Transferring the Game of Life to a continuous domain means extending it from a discrete grid to a continuous space, where cells are represented as points in a continuous plane, and their states evolve continuously instead of step-by-step. In this extended version, each cell's state can be a real number between 0 and 1, representing the level of activity or "aliveness" of that cell. The neighboring cells' activity levels will influence each other, leading to continuous patterns and dynamics.

References:  

https://arxiv.org/pdf/1111.1567.pdf   

https://www.youtube.com/c/TsodingDaily

Dependencies: 

C++  
raylib  
JsonCpp  

To install raylib:
```bash
$ sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
$ git clone https://github.com/raysan5/raylib
$ cd raylib
$ mkdir build && cd build
$ cmake -DBUILD_SHARED_LIBS=ON ..
$ make up
$ sudo make install
$ sudo cp /usr/local/lib/libraylib.so.450 /usr/lib/
```
NOTE! if you get and error that /usr/local/lib/libraylib.so.450 doesnt exist just go to /usr/local/lib and there should be file libraylib.so.4xx so unsetad of 450 just write whatever number is there. This error occurs because of version diff.

To install JsonCpp:
```bash
$ sudo apt-get install libjsoncpp-dev
```
To build everything just run:
```bash
./build.sh
```
NOTE! You may have to run:
```bash
chmod +x build.sh
```
To run the program:
```bash
./smooth_life_terminal
```
for terminal version or:
```bash
../smooth_life_gpu preset_name.json
```
NOTE! You can create your own presets, just add them to /presets/gpu_presets folder and just pass preset name as an argument when running the code Or  you can mess with the terminal presets just save them and run the code.

```json{
    "fps":60, // frames per second also ahs impact on cell creation
    "init":4, // the way you init the board
    "factor": 50, // basically sets the screen size
    "scalar": 0.6, // sets resolution 
    "ra": 43.50, // size of the cells
    "alpha_n": 0.028, // width of the step for anti aliasing
    "alpha_m": 0.147, // width of the step for anti aliasing
    "b1": 0.257, //
    "b2": 0.336, // birth and 
    "d1": 0.365, // death intervals
    "d2": 0.549, //
    "dt": 0.05 // cell developing speed
}
```
NOTE! You can get very interesting results by playing with init, ra and dt.


