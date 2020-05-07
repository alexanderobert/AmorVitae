cmake_minimum_required(VERSION 3.12)
project(AmorVitae)

set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build"
        )

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include"
            )
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

set(
        SERVER_HDRS
        server/include/ObjectManager.h
        server/include/Object.h
        server/include/Event.h
        server/include/EventManager.h
        server/include/World.h
        server/include/User.h
        server/include/PacketManager.h
)

set(
        SERVER_SRCS
        server/src/ObjectManager.cpp
        server/src/Object.cpp
        server/src/Event.cpp
        server/src/EventManager.cpp
        server/src/World.cpp
)

set(
        TEST_SERVER_SRC
        server/tests/EventTest.cpp
        server/tests/ObjectTest.cpp
        server/tests/main.cpp
)
include_directories(cmake-build-debug/googletest-src/googlemock/include)
include_directories(cmake-build-debug/googletest-src/googletest/include)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#include_directories(${SERVER_HDRS})

set (SERVER ${SERVER_HDRS} ${SERVER_SRCS} server/include/CollisionManager.h)
set (TEST_SERVER ${SERVER_HDRS} ${TEST_SERVER_SRC})

add_library(server_lib STATIC ${SERVER})

add_executable(AmorVitaeServer server/src/main.cpp)
add_executable(server_test ${TEST_SERVER})

target_link_libraries(AmorVitaeServer server_lib)
target_link_libraries(server_test gtest gtest_main)
