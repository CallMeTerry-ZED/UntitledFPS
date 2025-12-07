# UntitledFPS

A FPS game/engine written in modern C++ and OpenGL.

Feel free to join us on [Discord](https://discord.gg/NmQwqfsCD7).

Heavily Inspired By the Chernos Hazel Engine project, [Hazel](https://github.com/TheCherno/Hazel).

## "From Scratch"

Planned features such as:
- Lua scripting
- Bullet3 physics
- Custom networking
- Custom animations
- 2.5D raycasting with planned full 3D rendering
- Cross platfrom support
- And much more

## Building

This project uses a MakeFile wrapper around CMake for building.
This project will only build and run on linux but we plan to support other platfroms such as:
- MacOS
- Windows
- VR/AR
- Consoles

### Build Commands

**Release Build (default):**
```bash
make build    # Configure and build in Release mode
make run      # Build and run the executable
```

**Debug Build:**
```bash
make debug-build  # Configure and build in Debug mode
make debug-run    # Build and run in Debug mode
```

**Other Commands:**
```bash
make config   # Only configure CMake (no build)
make clean    # Remove build directory
```

**Override Build Type:**
```bash
make build BUILD_TYPE=Debug    # Build Debug using regular target
make run BUILD_TYPE=Debug      # Build and run Debug
```

The build output will be in the `build/` directory, with the executable at `build/bin/FPS`.

## COPYRIGHT

Copyright (c) 2025 ZED Interactive. All Rights Reserved.
