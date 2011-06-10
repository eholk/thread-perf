cmake_minimum_required(VERSION 2.8)
project(thread-perf)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LIBRARIES pthread rt)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_executable(thread-create thread-create.cpp)
target_link_libraries(thread-create ${LIBRARIES})
add_executable(many-thread-create many-thread-create.cpp)
target_link_libraries(many-thread-create ${LIBRARIES})
add_executable(loaded-thread-create loaded-thread-create.cpp)
target_link_libraries(loaded-thread-create ${LIBRARIES})
