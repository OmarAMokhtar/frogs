cmake_minimum_required(VERSION 3.0)

project(FrogsExamples)

add_executable(UnitsExample example/units_example.cpp src/frogs.cpp)
target_include_directories(UnitsExample PRIVATE src)
target_compile_features(UnitsExample PRIVATE cxx_std_17)

add_executable(ExpressionsExample example/expressions_example.cpp src/frogs.cpp)
target_include_directories(ExpressionsExample PRIVATE src)
target_compile_features(ExpressionsExample PRIVATE cxx_std_17)

add_executable(DifferentiationExample example/differentiation_example.cpp src/frogs.cpp)
target_include_directories(DifferentiationExample PRIVATE src)
target_compile_features(DifferentiationExample PRIVATE cxx_std_17)

add_executable(VectorsExample example/vectors_example.cpp src/frogs.cpp)
target_include_directories(VectorsExample PRIVATE src)
target_compile_features(VectorsExample PRIVATE cxx_std_17)

add_executable(MatrixExample example/matrix_example.cpp src/frogs.cpp)
target_include_directories(MatrixExample PRIVATE src)
target_compile_features(MatrixExample PRIVATE cxx_std_17)
