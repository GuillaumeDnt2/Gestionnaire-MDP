cmake_minimum_required(VERSION 3.10)

# set the project name
project(Test VERSION 0.1 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify the output directories for build artifacts
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- OpenSSL detection (robuste) ---
find_package(OpenSSL REQUIRED)

if (NOT OpenSSL_FOUND)
    message(FATAL_ERROR "OpenSSL introuvable ! Installe openssl-devel sur Fedora.")
endif()

message(STATUS "OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL libraries  : ${OPENSSL_LIBRARIES}")

# --- Add executable ---
add_executable(Test
    ./src/main.cpp
    ./src/Console/LinuxConsole.cpp
    ./src/Menu/Menu.hpp
    ./src/Encryption/AES.cpp
)

# --- Include directories ---
target_include_directories(Test PRIVATE ${OPENSSL_INCLUDE_DIR})

# --- Link OpenSSL ---
target_link_libraries(Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
