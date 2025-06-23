cmake_minimum_required(VERSION 3.10)

# Project name and language
project(run LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory for header files
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp 
    src/client.cpp  
    src/handler.cpp
    src/server.cpp   
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})