cmake_minimum_required(VERSION 3.0)
project(home_security)
find_package( Threads )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp ConnectionMap.cpp MachinesConnection.cpp
        LocalMonitor.cpp Communicator.cpp
        abstract_socket/CrossPlatformSocket.cpp)
add_executable(home_security ${SOURCE_FILES})
target_link_libraries(home_security tins ${Boost_LIBRARIES})