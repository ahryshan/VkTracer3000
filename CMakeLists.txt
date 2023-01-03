cmake_minimum_required(VERSION 3.23)
project(VkTracer3000)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE _SRCS src/*.cpp include/*.h)
include_directories(include)

add_executable(VkTracer3000 ${_SRCS})
