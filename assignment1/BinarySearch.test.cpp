#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "BinarySearch.hpp"
#include "doctest/doctest.h"
#include <vector>

TEST_CASE("Test binary search") {
  std::vector<int> sorted = {1, 2, 3, 4, 5, 6};

  SUBCASE("When the target is present, return the correct index") {
    CHECK(BinarySearch(sorted, 1) == 0);
    CHECK(BinarySearch(sorted, 3) == 2);
  }

  SUBCASE("When the target is missing, return -1") {
    CHECK(BinarySearch(sorted, 27) == -1);
    CHECK(BinarySearch(sorted, -12) == -1);
  }
}