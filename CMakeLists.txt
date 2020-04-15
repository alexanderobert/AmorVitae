cmake_minimum_required(VERSION 3.15)
project(skeleton)

set(CMAKE_CXX_STANDARD 14)

add_executable(skeleton main.cpp clientManager.cpp clientManager.h player.cpp player.h position.cpp position.h clickProcessing.cpp clickProcessing.h requestManager.cpp requestManager.h responseManager.cpp responseManager.h displayObject.cpp displayObject.h)