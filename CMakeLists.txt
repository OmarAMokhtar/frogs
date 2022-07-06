cmake_minimum_required(VERSION 3.0)

project(FrogsTestProj)

add_executable(FrogsTest
    example/example.cpp
    src/frogs_expressions.cpp
)

target_include_directories(FrogsTest
    PRIVATE
        src
)

target_compile_features(FrogsTest PRIVATE cxx_std_17)
