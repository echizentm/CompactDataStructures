cmake_minimum_required(VERSION 3.7)
add_definitions("-Wall -std=c++11 -O2 -march=native")
include_directories(../cds/)
add_executable(
    compressed_bit_vector_sample
    compressed_bit_vector_sample.cpp
)
add_executable(
    rank_sample
    rank_sample.cpp
)
target_link_libraries(compressed_bit_vector_sample cds)
target_link_libraries(rank_sample cds)
