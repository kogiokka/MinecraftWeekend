# Minecraft Weekend

This repo is a fork of [jdah's minecraft-weekend](https://github.com/jdah/minecraft-weekend/tree/387ecb554946180094d58c57a4ee216dba506cc4) for me to learn game programming and tinker with project management.

![screenshot](screenshots/1.png)

## Features
- Infinite, procedurally generated world
- Infinite height/depth
- Day/night cycle
- Biomes
- ECS-driven player and entities with full collision and movement
- Full RGB lighting
- Full transparency + translucency support
- Sprite blocks (flowers)
- Animated blocks (water + lava)
- Distance fog
- A whole lot of different block types
- More

## Prerequisites

This project requires `CMake` and `git` to manage dependencies and build:

Ubuntu/Debian
```sh
sudo apt-get install cmake git
```

Fedora/CentOS
```sh
sudo dnf install cmake git
```

This project uses the following external libraries:

 * `GLFW>=3.36`
 * `cglm>=0.8.4`
 * `glad`
 * `noise1234`
 * `stb_image`

`GLFW` and `cglm` will be downloaded to `lib/` with CMake `FetchContent` at the first run.
The rest of the libraries have been integrated into this repo under `lib/`, no extra steps to acquire them.

## Build
### Unix-like

```sh
# Change working directory to project root
cd MinecraftWeekend/;

# Debug build
cmake -B build/Debug \
      -D CMAKE_BUILD_TYPE=Debug;
cmake --build build/Debug;

# Release build
cmake -B build/Release \
      -D CMAKE_BUILD_TYPE=Release;
cmake --build build/Release;
```

The `game` binary can be found in `build/<Debug|Release>` once `cmake --build` is finished.

### Windows

Not yet tested. Currently, the source code contains C dialect only available to compile with GCC and Clang.
