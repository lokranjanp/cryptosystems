cmake_minimum_required(VERSION 3.28)
project(cryptsystems)

set(CMAKE_CXX_STANDARD 17)

add_executable(cryptsystems algorithms.cpp
        rsa.cpp
        algorithms.h
        rsa.h
        main.cpp)
