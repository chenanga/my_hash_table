cmake_minimum_required(VERSION 3.28)
project(my_hash_table)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(my_hash_table
        src/hash_table.c
        src/hash_table.h
        src/main.c
        src/prime.c
        src/prime.h)
