# The Ray Tracer Challenge in C++

This repository is to implement the algorithm and the tests described in the [The Ray Tracer Challenge Book](http://raytracerchallenge.com/) using C++.

## Requirement

- C++ compiler with C++17 support
- CMake
- Conan
- Ninja (optional)

## Compile

```bash
conan profile detect --force # if you used Conan before this step isn't required.
conan install . --output-folder=build --build=missing
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -GNinja
cmake --build .
```
