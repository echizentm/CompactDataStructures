cmake_minimum_required(VERSION 3.7)
add_definitions("-Wall -std=c++11 -O2")
add_library(
    cds
    SHARED
    bit_vector.cpp
    fixed_length_vector.cpp
    sampled_pointers.cpp
    dense_pointers.cpp
)
