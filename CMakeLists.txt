cmake_minimum_required(VERSION 3.10)
project(Render_Engine)

set(CMAKE_CXX_STANDARD 17)

# Find GLFW
find_package(glfw3 REQUIRED)

# Create executable
add_executable(Render_Engine main.cpp)

# Include directories (optional since GLAD is global, but safe)
include_directories(/usr/local/include)

# Link libraries
target_link_libraries(Render_Engine
    glfw
    glad       
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
    m
)

