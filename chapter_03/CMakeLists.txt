cmake_minimum_required(VERSION 2.8)
add_definitions("-Wall -std=c++11 -O2")
add_executable(
    bit_vector_sample
    bit_vector_sample.cpp
    cds/bit_vector.cpp
)
add_executable(
    fixed_length_vector_sample
    fixed_length_vector_sample.cpp
    cds/bit_vector.cpp
    cds/fixed_length_vector.cpp
)
add_executable(
    sampled_pointers_sample
    sampled_pointers_sample.cpp
    cds/bit_vector.cpp
    cds/sampled_pointers.cpp
)
