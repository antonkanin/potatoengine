**How to build on Linux**

```
git clone https://gitlab.com/antonkanin/gamedev_specialforces
mkdir build
cd build
cmake . ..
cmake --build .
```

Special note for the dynamic library task 01-03-hello-lib-dynamic, Linux does not see *.so library files in the same folder as the application by defult, you might need to tell it to look in the current folder by running this command:
```
export LD_LIBRARY_PATH=.
```

