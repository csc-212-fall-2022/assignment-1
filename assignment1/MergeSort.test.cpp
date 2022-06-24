//
// Created by csar on 6/20/22.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "MergeSort.hpp"
#include "doctest/doctest.h"
#include <vector>

TEST_CASE("Test merge sort") {
  std::vector<int> sorted = {1, 2, 3};
  std::vector<int> scrambled = {2, 1, 3};
  CHECK(MergeSort(sorted) == sorted);
  CHECK(MergeSort(scrambled) == sorted);
};
