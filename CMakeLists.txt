cmake_minimum_required(VERSION 3.12)
project(AmorVitae)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
        server
        server/include
        server/include/CollisionManager.h
        server/include/Object.h
        server/include/Event.h
        server/include/EventManager.h
        server/include/World.h
        server/include/ObjectManager.h
)

set(
        SERVER_SRCS
        server
        server/src
        server/src/ObjectManager.cpp
        server/src/CollisionManager.cpp
        server/src/Object.cpp
        server/src/Event.cpp
        server/src/EventManager.cpp
        server/src/World.cpp
)

set(
        NET_SRC_SERVER
        Net
        Net/src
        Net/src/NetServer.cpp
        Net/src/User.cpp
        Net/src/PacketManagerServer.cpp
)
set(
        NET_SRC_CLIENT
        Net/src
        Net/src/NetClient.cpp
        Net/src/PacketManager.cpp
)
set(
        NET_HDRS_SERVER
        Net
        Net/include
        Net/include/message_server.h
        Net/include/NetServer.h
        Net/include/User.h
        Net/include/PacketManagerServer.h
)
set(
        NET_HDRS_CLIENT
        Net
        Net/include
        Net/include/message_client.h
        Net/include/NetClient.h
        Net/include/PacketManager.h
        Net/include/message_client.h
)
set(
        CLIENT_HDRS
        client
        client/include
        client/include/actionManager.h
        client/include/actionServer.h
        client/include/stuctClient.h
)
set(
        CLIENT_SRC
        client
        client/src
        client/src/actionManager.cpp
        client/src/actionServer.cpp
        client/src/main.cpp
)
set (
        GRAPHICS_HDRS
        graphics
        graphics/include
        graphics/include/graphicsManager.h
        graphics/include/PlayerModel.h
        graphics/include/ProjectileModel.h
        graphics/include/struct_Config.h
        graphics/include/ObstacleModel.h
)

set (
        GRAPHICS_HDRS
        graphics
        graphics/src
        graphics/src/graphicsManager.cpp
        graphics/src/PlayerModel.cpp
        graphics/src/ProjectileModel.cpp
        graphics/src/ObstacleModel.cpp
)

include_directories(cmake-build-debug/googletest-src/googlemock/include)
include_directories(cmake-build-debug/googletest-src/googletest/include)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

set (NET_SERVER ${NET_HDRS_SERVER} ${NET_SRC_SERVER})
set (NET_CLIENT ${NET_HDRS_CLIENT} ${NET_SRC_CLIENT})
set (SERVER ${SERVER_HDRS} ${SERVER_SRCS})
set (TEST_SERVER ${SERVER_HDRS} ${TEST_SERVER_SRC})
set (CLIENT ${CLIENT_SRC} ${CLIENT_HDRS})
set (GRAPHICS ${GRAPHICS_HDRS} ${GRAPHICS_HDRS})


include_directories(
        server
        server/include
        server/src
        Net
        Net/include
        Net/src
        client
        client/include
        client/src
        graphics
        graphics/include
        graphics/src
)

add_executable(AmorVitaeServer server/src/main.cpp ${SERVER} ${NET_SERVER})
add_executable(server_test ${TEST_SERVER})
add_executable(AmorVitaeClient client/src/main.cpp ${CLIENT} ${GRAPHICS} ${NET_CLIENT})

target_link_libraries(AmorVitaeServer ${Boost_LIBRARIES})
target_link_libraries(AmorVitaeClient ${SFML_LIBRARIES})
target_link_libraries(server_test gtest gtest_main)
target_link_libraries(AmorVitaeClient ${Boost_LIBRARIES})