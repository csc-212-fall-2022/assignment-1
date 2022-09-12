#include "BinarySearch.hpp"
#include <vector>

auto BinarySearch(const std::vector<int> &vec, int target) -> int {
  int n = vec.size();
  int left = 0;
  int right = n - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (target == vec.at(mid)) {
      return mid;
    } else if (target < vec.at(mid)) {
      // move left
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return -1;
}