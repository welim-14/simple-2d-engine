# Simple 2D Physics Engine

A lightweight 2D physics engine written in modern C++ using SFML for rendering.

The goal of this project is to learn and demonstrate the fundamentals behind a physics engine, including rigid body dynamics, collision detection, collision resolution, and mathematical foundations, while keeping the rendering layer independent from the physics engine.

> **Note:** This project is currently under active development.

---

## Features

### Current

- ✅ Custom `Vec2` math class
- ✅ Vector arithmetic operators
- ✅ Dot product
- ✅ Vector normalization
- ✅ Length and squared length calculations

### Planned

- Rigid bodies
- Circle and rectangle colliders
- Gravity
- Collision detection
- Collision resolution using impulses
- Rotational dynamics
- Broad-phase collision detection
- Interactive sandbox
- Debug visualization

---

The physics engine is completely independent from SFML. SFML is only used to render the simulation inside the sandbox application.

---

## Technologies

- C++17
- SFML 3

---

## Building

```bash
git clone https://github.com/welim-14/simple-2d-engine.git
cd simple-2d-engine

cmake -B build
cmake --build build

./build/bin/Sandbox
```

---

## Roadmap

- [x] Mathematical vector class (`Vec2`)
- [ ] Shapes
- [ ] RigidBody
- [ ] World
- [ ] Gravity
- [ ] Collision detection
- [ ] Collision resolution
- [ ] Interactive sandbox
- [ ] Unit tests

---

## License

MIT License
