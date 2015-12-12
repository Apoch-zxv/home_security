cmake_minimum_required(VERSION 3.0)
project(home_security)
find_package( Threads )
find_package(Boost 1.40.0 REQUIRED system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp ConnectionMap.cpp ConnectionMap.h MachinesConnection.cpp MachinesConnection.h
        LocalMonitor.cpp LocalMonitor.h
        Communicator.cpp Communicator.h)
add_executable(home_security ${SOURCE_FILES})
target_link_libraries(home_security tins ${Boost_LIBRARIES})