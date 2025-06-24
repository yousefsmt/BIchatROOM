cmake_minimum_required(VERSION 3.10)

project(BIchatROOM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Client src/client.cpp)
add_executable(Server src/server.cpp)