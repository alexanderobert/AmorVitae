cmake_minimum_required(VERSION 3.15)
project(skeleton)

set(CMAKE_CXX_STANDARD 14)

add_executable(skeleton main.cpp event.cpp event.h actionManager.cpp actionManager.h clientConnection.cpp clientConnection.h actionServer.cpp actionServer.h displayManager.cpp displayManager.h)