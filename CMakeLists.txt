cmake_minimum_required(VERSION 3.10)
project(CommandPack)

# Use C++17 for filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all cpp files in src/
file(GLOB CMD_SOURCES src/*.cpp)

# Build each .cpp file into a separate executable
foreach(cmd ${CMD_SOURCES})
    get_filename_component(cmdname ${cmd} NAME_WE)
    add_executable(${cmdname} ${cmd})
endforeach()
