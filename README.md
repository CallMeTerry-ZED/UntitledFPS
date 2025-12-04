# UntitledFPS

A small FPS game written in modern C++ and OpenGL.

Feel free to join us on [Discord](https://discord.gg/NmQwqfsCD7).

## "From Scratch"

Planned features such as:
- Lua scripting

## Building

This project uses a MakeFile wrapper around CMake for building.

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
