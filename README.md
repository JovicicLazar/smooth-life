# smooth-life
Game of life transfered to a continuous domain

Dependencies 
C++
raylib
JsonCpp

To install raylib
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

To install JsonCpp
```sh
$ sudo apt-get install libjsoncpp-dev
```
