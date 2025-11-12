cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(BIchatRoom
    VERSION 1.0.0
    DESCRIPTION "Constrained Application Protocol"
    LANGUAGES CXX
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
        message(FATAL_ERROR "GCC >= 8.0 required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
        message(FATAL_ERROR "Clang >= 6.0 required")
    endif()
elseif(MSVC)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.20)
        message(FATAL_ERROR "MSVC >= 19.20 required (Visual Studio 2019+)")
    endif()
endif()

message(STATUS "Building ${PROJECT_NAME} v${PROJECT_VERSION} on ${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")

set(CLIENT_SOURCES
    src/client.cpp
)

set(SERVER_SOURCES
    src/server.cpp
)

include_directories(include)

add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})


# ================================
# Warnings & Security flags
# ================================
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(client PRIVATE 
        -Wall -Wextra -Wpedantic
        -Werror
        -Wconversion -Wsign-conversion
        -Wshadow
        -Wnull-dereference
        -fstack-protector-strong
        -fPIE -fPIC
        $<$<CONFIG:Release>:-O2>
    )
    target_compile_options(server PRIVATE 
        -Wall -Wextra -Wpedantic
        -Werror
        -Wconversion -Wsign-conversion
        -Wshadow
        -Wnull-dereference
        -fstack-protector-strong
        -fPIE -fPIC
        $<$<CONFIG:Release>:-O2>
    )
endif()

# ================================
# Static analysis (optional)
# ================================
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(client PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    )
    set_target_properties(server PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    )
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i
            ${CLIENT_SOURCES} ${SERVER_SOURCES}
            ${CMAKE_SOURCE_DIR}/include/*.h
        COMMENT "Running clang-format on sources"
    )
endif()

find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
    message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
    set(CMAKE_CXX_CPPCHECK
        "${CPPCHECK_EXE};--enable=all;--inconclusive;--quiet;--std=c++17")
else()
    message(WARNING "cppcheck not found!")
endif()

option(ENABLE_SANITIZERS "Enable runtime sanitizers" ON)
if(ENABLE_SANITIZERS AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(client PRIVATE -fsanitize=address,undefined)
        target_link_options(client PRIVATE -fsanitize=address,undefined)
        target_compile_options(server PRIVATE -fsanitize=address,undefined)
        target_link_options(server PRIVATE -fsanitize=address,undefined)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(client PRIVATE
        -D_FORTIFY_SOURCE=2
        -fstack-clash-protection
    )
    target_compile_options(server PRIVATE
        -D_FORTIFY_SOURCE=2
        -fstack-clash-protection
    )
endif()