# The Ray Tracer Challenge in C++

This repository is to implement the algorithm and the tests described in the [The Ray Tracer Challenge Book](http://raytracerchallenge.com/) using C++.

## Requirement

- C++ compiler with C++17 support
- CMake
- Conan
- Ninja (optional)

## Compile

### Build release with ninja

```bash
conan profile detect --force # if you used Conan before this step isn't required.
conan install . --output-folder=build --build=missing
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..
cmake --build .
```

### Build debug with ninja

```bash
conan profile detect --force # if you used Conan before this step isn't required.
conan install . --output-folder=build --build=missing --settings=build_type=Debug
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -GNinja ..
cmake --build . --config Debug
```

## Todos

- [ ] Rewrite `Canvas::to_ppm`