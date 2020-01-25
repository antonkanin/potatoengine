**How to build on Linux**

```
git clone https://gitlab.com/antonkanin/swat
mkdir build
cd build
cmake . ..
cmake --build .
```

Special note for the dynamic library task 01-03-hello-lib-dynamic, Linux does not see *.so library files in the same folder as the application by defult, you might need to tell it to look in the current folder by running this command:
```
export LD_LIBRARY_PATH=.
```

**How to build on Windows**

The easiest way is to get MSYS2 installed and get all the packages with pacman
```
pacman -S mingw-w64-x86_64-bullet mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-yaml-cpp mingw-w64-x86_64-assimp mingw-w64-x86_64-glm
```
