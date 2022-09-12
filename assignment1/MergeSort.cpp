#include "MergeSort.hpp"
#include <vector>

auto MergeSort(const std::vector<int> &vec) -> std::vector<int> {
  if (vec.size() <= 1) {
    return vec;
  }
  std::vector<int> front = {};
  std::vector<int> back = {};
  // stick the front half of vector onto front and the back onto back
  for (int i = 0; i < vec.size(); i++) {
    if (i < vec.size() / 2) {
      front.push_back(vec.at(i));
    } else {
      back.push_back(vec.at(i));
    }
  }
  std::vector<int> sorted_front = MergeSort(front);
  std::vector<int> sorted_back = MergeSort(back);

  std::vector<int> result = {};
  int i = 0;
  int j = 0;
  while (i < sorted_front.size() && j < sorted_back.size()) {
    if (sorted_front.at(i) < sorted_back.at(j)) {
      result.push_back(sorted_front.at(i));
      i++;
    } else {
      result.push_back(sorted_back.at(j));
      j++;
    }
  }

  // run out the arrays
  while (i < sorted_front.size()) {
    result.push_back(sorted_front.at(i));
    i++;
  }
  while (j < sorted_back.size()) {
    result.push_back(sorted_back.at(j));
    j++;
  }
  return result;
}