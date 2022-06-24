cmake_minimum_required(VERSION 3.14)

project("assignment1")

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake) # make sure we know where to find the doctest header

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/assignment1)
find_package(Doctest REQUIRED)

include(cmake/ClangFormat.cmake)

enable_testing()

find_program(CLANG_TIDY_EXE NAME clang-tidy REQUIRED)
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*,bugprone-*")

add_library(MergeSort assignment1/MergeSort.hpp assignment1/MergeSort.cpp)
add_library(BinarySearch assignment1/BinarySearch.cpp assignment1/BinarySearch.hpp)
set_target_properties(MergeSort PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
set_target_properties(BinarySearch PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

add_executable(MergeSortTests assignment1/MergeSort.test.cpp)
target_compile_features(MergeSortTests PRIVATE cxx_std_17)
target_link_libraries(MergeSortTests Doctest MergeSort)
add_test(NAME MergeSortTests COMMAND MergeSortTests)

add_executable(BinarySearchTests assignment1/BinarySearch.test.cpp)
target_compile_features(BinarySearchTests PRIVATE cxx_std_17)
target_link_libraries(BinarySearchTests Doctest BinarySearch)
add_test(NAME BinarySearchTests COMMAND BinarySearchTests)