# /*
#  * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
#  */

cmake_minimum_required(VERSION 3.10)
project(stb)

# Create a static library for stb_image implementation
add_library(stb STATIC stb_image.cpp)

# Make the headers visible to any target that links stb
target_include_directories(stb
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Set C++ standard (stb_image is C-compatible but we compile as C++)
set_target_properties(stb PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

