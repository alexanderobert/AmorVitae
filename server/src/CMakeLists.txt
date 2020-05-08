cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src
        CollisionManager.cpp
        Event.cpp
        EventManager.cpp
        main.cpp
        Object.cpp
        ObjectManager.cpp
        World.cpp)
