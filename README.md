# Simple 2D Physics Engine

A lightweight 2D physics engine written in C++ using SFML for rendering.

The goal of this project is to learn and demonstrate the fundamentals behind a physics engine, including rigid body dynamics, collision detection, collision resolution, and mathematical foundations, while keeping the rendering layer independent from the physics engine.

> **Note:** This project is currently under active development.

---

## Features

- Custom vector2 math class
- Rigid bodies
- Collisions for circles and boxes
- Gravity simulation
- Collision detection and resolution
- Interactive sandbox

> The physics engine is completely independent from SFML. SFML is only used to render the simulation inside the sandbox application.

## Technologies

- C++17
- SFML 3 for rendering


## Compatibility

This project is meant to be available for  **Linux**, **Windows** and **MacOS** since the required dependencies are available in all platforms.  
However, it's important to note that currently it has only been tested on a **Linux** environment.

## Pre-requisites

- A C++17 compiler (GCC, Clang, MSVC)  
- [CMake](https://cmake.org/download/)
- [Git](https://git-scm.com/install/)

### System dependencies (Linux only)

In Linux systems, the SFML dependencies need to be installed using the system package manager.  
  
For Arch Linux:
 ```bash
 sudo pacman -S base-devel freetype2 libx11 libxrandr libxcursor libxi libglvnd alsa-lib openal flac libvorbis
```

For Ubuntu/Debian:
 ```bash
sudo apt-install build-essential libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev libfreetype6-dev
```

## Building

```bash
git clone https://github.com/welim-14/simple-2d-engine.git
cd simple-2d-engine
```

```bash
cmake -B build
cmake --build build
```

```bash
./build/bin/Sandbox
```

## License

MIT License
