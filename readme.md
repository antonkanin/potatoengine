###About
Hand-made 3D game engine inspired by the offline [C++ Game Development course](https://www.it-academy.by/course/c-game-developer/game-developer/) I took in 2019 (the course in only in Russian, sorry).



###How to build
**Linux**

Install dependencies.

```
sudo apt install libsdl2-dev libsdl2-mixer-dev libbullet-dev libglm-dev libyaml-cpp-dev
```
Get the code and build
```
git clone https://github.com/antonkanin/potatoengine
mkdir build && cd build
cmake ..
make
```


**Windows**

The easiest way is to install MSYS2 and get all the packages with pacman
```
pacman -S mingw-w64-x86_64-bullet mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-yaml-cpp mingw-w64-x86_64-assimp mingw-w64-x86_64-glm
```
