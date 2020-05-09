cmake_minimum_required(VERSION 3.12)
project(AmorVitae)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(AmorVitae main.cpp)

target_link_libraries(AmorVitae sfml-graphics sfml-audio sfml-window sfml-system)