cmake_minimum_required(VERSION 3.15)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(client main.cpp clientConnection.cpp clientConnection.h json.hpp actionServer.cpp actionServer.h displayManager.cpp displayManager.h)

target_link_libraries(client sfml-graphics sfml-audio)

