# Geometry

It uses the uses [CMake][] as a build system.</br>

## Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data
```

## Build instructions
```sh
# Clone this repo
git clone https://github.com/trpo2023/geometry-t1m3ctrl.git
cd geometry-t1m3ctrl

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./geometry
```

[CMake]: https://cmake.org
[Git]: https://git-scm.com