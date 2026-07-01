cmake_minimum_required(VERSION 3.20)

# Project
project(TealangCompiler 
    VERSION 0.0.0 
    LANGUAGES CXX
    DESCRIPTION "Tealang Compiler"
)

# C++ Standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

# Main executable
add_executable(tea ${SOURCES})

target_include_directories(tea PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_features(tea PRIVATE cxx_std_23)