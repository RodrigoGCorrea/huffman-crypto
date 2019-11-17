cmake_minimum_required(VERSION 3.13)

project(huffman_crypto)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -O2 -pedantic")

add_executable(huffman_crypto main.c b-tree/b-tree.c huffman-tree/huffman-tree.c)
