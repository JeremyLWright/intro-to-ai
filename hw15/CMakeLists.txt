project(hw15)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall ")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(quan)
include_directories(visualization)
Find_Package(Boost COMPONENTS program_options system filesystem regex)
include_directories(${Boost_INCLUDE_DIRS}) 
add_executable(hw15 main.cpp) 
target_link_libraries(hw15 ${Boost_LIBRARIES})     
