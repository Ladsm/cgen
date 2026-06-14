
# Cgen

##### CMake Generator and C/C++ Helper

---

Cgen is a program made to make the cmake experience easier.

Example usage:
```sh
[ladsm@DESKTOP-1PIOFP7 documents]$ cgen init example
[ladsm@DESKTOP-1PIOFP7 documents]$ cd example
[ladsm@DESKTOP-1PIOFP7 example]$ cgen build
-- The CXX compiler identification is GNU 16.1.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/sbin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (3.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ladsm/documents/example/build
[ 33%] Building CXX object CMakeFiles/example.dir/cmake_pch.hxx.gch
[ 66%] Building CXX object CMakeFiles/example.dir/src/main.cpp.o
[100%] Linking CXX executable example
[100%] Built target example
[ladsm@DESKTOP-1PIOFP7 example]$ cgen run
Hello, World!
[ladsm@DESKTOP-1PIOFP7 example]$ cgen add example_class --class
[ladsm@DESKTOP-1PIOFP7 example]$ tree -I "build"
.
|-- CMakeLists.txt
|-- include
|   |-- example_class.hpp
|   `-- pch.h
`-- src
    |-- example_class.cpp
    `-- main.cpp

3 directories, 5 files
[ladsm@DESKTOP-1PIOFP7 example]$
```

As you can see, it makes a cmake directory, builds it, runs it and can even add a new class.
