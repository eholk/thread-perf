cmake_minimum_required(VERSION 2.8)
project(thread-perf)

add_executable(thread-create thread-create.cpp)
add_executable(many-thread-create many-thread-create.cpp)
add_executable(loaded-thread-create loaded-thread-create.cpp)
