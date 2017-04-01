cmake_minimum_required(VERSION 3.7)
add_definitions("-Wall -std=c++11 -O2 -march=native")
add_library(
    cds
    SHARED
    bit_vector.cpp
    fixed_length_vector.cpp
    partial_sums.cpp
    variable_length_vector/sampled_pointers.cpp
    variable_length_vector/dense_pointers.cpp
    variable_length_vector/direct_access_codes.cpp
    variable_length_vector/elias_fano_codes.cpp
    compressed_bit_vector.cpp
    bit_vector_rank.cpp
)
