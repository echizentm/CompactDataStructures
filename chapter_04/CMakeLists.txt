cmake_minimum_required(VERSION 3.7)
add_definitions("-Wall -std=c++11 -O2")
include_directories(../cds/)
link_directories(../cds/build/)
add_executable(
    compressed_bit_vector_sample
    compressed_bit_vector_sample.cpp
)
target_link_libraries(compressed_bit_vector_sample cds)
