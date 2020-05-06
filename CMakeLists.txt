cmake_minimum_required(VERSION 3.12)
project(AmorVitae)
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

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

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
include_directories(cmake-build-debug/googletest-src/googlemock/include)
include_directories(cmake-build-debug/googletest-src/googletest/include)
include_directories(
        Net
        Net/include
        Net/include/NetClient.h
        Net/include/NetServer.h
        Net/include/PacketManager.h
        Net/include/User.h
        Net/include/Object.h
        Net/src
        Net/src/NetClient.cpp
        Net/src/NetServer.cpp
        Net/src/PacketManager.cpp
        Net/src/User.cpp
        Net/include/message_client.h
        Net/include/message_server.h
)


set(
        NET_SRC_SERVER

        Net/src/NetServer.cpp
        Net/src/PacketManager.cpp
        Net/src/User.cpp
)
set(
        NET_SRC_CLIENT

        Net/src/NetClient.cpp
        Net/src/PacketManager.cpp
)
set(
        NET_HDRS_SERVER

        Net/include/NetServer.h
        Net/include/PacketManager.h
        Net/include/User.h
        Net/include/Object.h
        Net/include/message_server.h
)
set(
        NET_HDRS_CLIENT

        Net/include/NetClient.h
        Net/include/PacketManager.h
        Net/include/Object.h
        Net/include/message_client.h
)


set(CMAKE_CXX_STANDARD 14)

add_executable(client client_test.cpp ${NET_SRC_CLIENT} ${NET_HDRS_CLIENT})
add_executable(server server_test.cpp ${NET_SRC_SERVER} ${NET_HDRS_SERVER})
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server ${Boost_LIBRARIES})




add_executable(test Net/tests/packet_test.cpp Net/tests/bind_test.cpp ${NET_SRC_SERVER} ${NET_HDRS_SERVER})
target_link_libraries(test gtest gtest_main)
