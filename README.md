# Simple 2D Game Engine (OpenGL + GLFW)

## Overview

This project is a simple modular 2D game engine written in C++ using OpenGL and GLFW.
The goal of this engine is to provide a reusable foundation for building future 2D games such as platformers, top-down shooters, puzzle games, and other small projects.

---

## Project Structure

```
include/
    Game.h
    GameObject.h
    Scene.h
    Renderer.h
    Transform.h
    RigidBody.h

src/
    main.cpp
    Game.cpp
    GameObject.cpp
    Scene.cpp
    Renderer.cpp
```

---

## Engine Architecture

```
main
 └── Game Loop
      ├── processInput
      ├── update
      └── render

Game
 └── Scene
      └── GameObjects

GameObject
 ├── Transform
 ├── RigidBody
 └── update()

Renderer
 └── draw()
```

### Responsibilities

**main.cpp**

* Initializes GLFW
* Creates window
* Initializes OpenGL (GLAD)
* Creates Renderer
* Creates Game
* Runs the game loop

**Game**

* Handles input
* Updates game logic
* Handles collisions
* Renders objects
* Manages the Scene

**Scene**

* Stores and updates all GameObjects

**GameObject**

* Stores Transform and RigidBody
* Updates its own movement

**Renderer**

* Handles drawing objects with OpenGL
* Handles projection and resizing

---

## Game Loop

The engine uses a standard game loop with delta time:

```
while (running)
    calculate deltaTime
    process input
    update game
    render
```

Delta time ensures movement is framerate independent.

---

## Controls

Current default controls:

| Key | Action     |
| --- | ---------- |
| W   | Move Up    |
| A   | Move Left  |
| S   | Move Down  |
| D   | Move Right |

---

## Features Implemented

* Delta time movement
* Orthographic projection
* Window resizing support
* Multiple GameObjects
* Scene system
* Basic collision detection
* Modular engine structure

---

## Future Improvements

Planned engine improvements:

- [ ] Object creation and deletion system
- [ ] Collision system separation
- [ ] Camera system
- [ ] Sprite/texture rendering
- [ ] Animation system
- [ ] Scene switching (menus, levels)
- [ ] Basic physics
- [ ] Audio
- [ ] Tilemap loading

---

## Building

Make sure you have installed:

* OpenGL
* GLFW
* GLAD
* GLM (for math)

Compile using your Makefile:

```
make
./game
```

---

## Purpose of This Project

This engine is intended to:

* Learn game engine architecture
* Practice C++ and OpenGL
* Serve as a reusable starting template for future games
* Understand game loops, rendering, physics, and entity systems

---

## Author

Tynan Guenther

University of Regina Computer Science Student

