cmake_minimum_required(VERSION 3.7)
add_definitions("-Wall -std=c++11 -O2 -march=native")
include_directories(../cds/)
add_executable(
    bit_vector_sample
    bit_vector_sample.cpp
)
add_executable(
    fixed_length_vector_sample
    fixed_length_vector_sample.cpp
)
add_executable(
    variable_length_vector_sample
    variable_length_vector_sample.cpp
)
add_executable(
    partial_sums_sample
    partial_sums_sample.cpp
)
target_link_libraries(bit_vector_sample cds)
target_link_libraries(fixed_length_vector_sample cds)
target_link_libraries(variable_length_vector_sample cds)
target_link_libraries(partial_sums_sample cds)
