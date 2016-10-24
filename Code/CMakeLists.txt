cmake_minimum_required(VERSION 3.5)
project(p2abce_idemix_contiki)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_subdirectory(util_sc)
include_directories(util_sc util_sc/p2abc_iot_toolkit_include)


add_subdirectory(util_sc_tests)



set(SOURCE_FILES main.cpp)
add_executable(p2abce_idemix_contiki ${SOURCE_FILES})
target_link_libraries(p2abce_idemix_contiki util_sc)