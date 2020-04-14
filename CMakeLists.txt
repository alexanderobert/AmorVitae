cmake_minimum_required(VERSION 3.12)
project(AmorVitae)

set(CMAKE_CXX_STANDARD 14)


add_executable(AmorVitae server/src/main.cpp server/src/ObjectManager.cpp server/include/ObjectManager.h server/src/Object.cpp server/include/Object.h server/src/Event.cpp server/include/Event.h server/src/EventManager.cpp server/include/EventManager.h server/src/World.cpp server/include/World.h)