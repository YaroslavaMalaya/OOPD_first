cmake_minimum_required(VERSION 3.26)
set(CMAKE_VERBOSE_MAKEFILE on)
project(cmakeProject)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "/Users/Yarrochka/Downloads/SFML-2.6.1-macOS-clang-64-bit/lib")

include_directories("/Users/Yarrochka/Downloads/SFML-2.6.1-macOS-Clang-64-bit/include")

link_directories("/Users/Yarrochka/Downloads/SFML-2.6.1-macOS-Clang-64-bit/lib")

add_executable(cmakeProject main.cpp)

target_link_libraries(cmakeProject sfml-graphics sfml-window sfml-system)
