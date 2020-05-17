cmake_minimum_required(VERSION 3.15)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(server
        include/CollisionManager.h
        include/Event.h
        include/EventManager.h
        include/Object.h
        include/ObjectManager.h
        include/World.h
        src/cmake-build-debug/cmake_install.cmake
        src/cmake-build-debug/CMakeCache.txt
        src/cmake-build-debug/Makefile
        src/cmake-build-debug/src.cbp
        src/CMakeLists.txt
        src/CollisionManager.cpp
        src/Event.cpp
        src/EventManager.cpp
        src/main.cpp
        src/Object.cpp
        src/ObjectManager.cpp
        src/World.cpp
        tests/EventTest.cpp
        tests/main.cpp
        tests/ObjectTest.cpp)

