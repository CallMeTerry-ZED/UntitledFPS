# /*
#  * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
#  */

cmake_minimum_required(VERSION 3.10)

project(FPS VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type defaults to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Project root
set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)

# ===========================
# Configure SpdLog
# ===========================
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_STATIC ON  CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF   CACHE BOOL "" FORCE)

# ===========================
# Configure GLFW
# ===========================
set(GLFW_BUILD_STATIC ON CACHE BOOL "Build GLFW as a static library" FORCE)
set(GLFW_BUILD_SHARED OFF CACHE BOOL "Disable shared library build" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# ===========================
# Add third-party libraries
# ===========================

# spdlog
add_subdirectory(${PROJECT_ROOT}/thirdparty/spdlog ${CMAKE_BINARY_DIR}/thirdparty/spdlog)

# glfw
add_subdirectory(${PROJECT_ROOT}/thirdparty/glfw ${CMAKE_BINARY_DIR}/thirdparty/glfw)


# glad
add_subdirectory(${PROJECT_ROOT}/thirdparty/glad ${CMAKE_BINARY_DIR}/thirdparty/glad)
# glm
add_subdirectory(${PROJECT_ROOT}/thirdparty/glm ${CMAKE_BINARY_DIR}/thirdparty/glm)

# imgui
add_subdirectory(${PROJECT_ROOT}/thirdparty/imgui-docking ${CMAKE_BINARY_DIR}/thirdparty/imgui)

# imguizmo
add_subdirectory(${PROJECT_ROOT}/thirdparty/imguizmo ${CMAKE_BINARY_DIR}/thirdparty/imguizmo)

# imgui-node-editor
add_subdirectory(${PROJECT_ROOT}/thirdparty/imgui-node-editor ${CMAKE_BINARY_DIR}/thirdparty/imgui-node-editor)

# ===========================
# Include directories
# ===========================
include_directories(
    ${PROJECT_ROOT}/include
    ${PROJECT_ROOT}/thirdparty/spdlog/include
    ${PROJECT_ROOT}/thirdparty/glfw/include
    ${PROJECT_ROOT}/thirdparty/glad
    ${PROJECT_ROOT}/thirdparty/glm/
    ${PROJECT_ROOT}/thirdparty/imgui-docking
    ${PROJECT_ROOT}/thirdparty/imgui-docking/backends
    ${PROJECT_ROOT}/thirdparty/imguizmo
    ${PROJECT_ROOT}/thirdparty/imgui-node-editor
)

# ===========================
# Source files
# ===========================
file(GLOB_RECURSE SOURCES
    "${PROJECT_ROOT}/src/**.cpp"
    "${PROJECT_ROOT}/src/**.c"
)

file(GLOB_RECURSE HEADERS
    "${PROJECT_ROOT}/include/**.h"
    "${PROJECT_ROOT}/include/**.hpp"
)

# ===========================
# Create executable
# ===========================
add_executable(${PROJECT_NAME} ${SOURCES})

# ===========================
# Link libraries
# ===========================
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
        glfw
        glad
        glm
        imgui
        imguizmo
        imgui_node_editor
)

# On Linux, you must also link against system OpenGL + pthread + dl + X11
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            GL
            pthread
            dl
            X11
            Xrandr
            Xi
            Xcursor
    )
endif()

# ===========================
# Compiler options
# ===========================
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /permissive-
    )
endif()

message(STATUS "")
message(STATUS "========== FPS Engine Build Summary ==========")
message(STATUS "C++ Standard:        ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type:          ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Prefix:      ${CMAKE_INSTALL_PREFIX}")
message(STATUS "================================================")
message(STATUS "")
