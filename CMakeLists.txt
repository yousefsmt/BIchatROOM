cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyCppProject LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory for header files
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp 
    src/admin.cpp  
    src/airport.cpp  
    src/customer.cpp  
    src/date.cpp  
    src/domesticcities.cpp  
    src/domesticflights.cpp  
    src/food.cpp  
    src/foreigncities.cpp  
    src/foreignflights.cpp   
    src/tax.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})