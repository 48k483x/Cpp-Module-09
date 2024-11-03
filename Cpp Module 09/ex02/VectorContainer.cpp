# include "PmergeMe.hpp"

/*
 * daba La kant [3, 5, 9, 7, 4]
  * first pair: [5, 3] ==> 3 & 5 are swapped cause 5 > 3
  * second pair: [9, 7]
  * Last element: (4) - become [-1, 4] since it's unpaired
  |
  * -> [(5, 3), (9, 7), (-1, 4)]
*/
std::vector<std::pair<int, int> > PmergeMe::getPairsVec(std::vector<int>& vec) {
  std::vector<std::pair<int, int> > pairs;
  /* Sort each pair internally (larger number becomes first)*/
  for (size_t i = 0; i < vec.size() - 1; i += 2) {
    if (vec[i] < vec[i + 1])
      std::swap(vec[i], vec[i + 1]);
  }
  /* crete pairs, handling odd length arrays */
  for (size_t i = 0; i < vec.size(); i += 2) {
    if (i + 1 < vec.size())
      pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
    else
      pairs.push_back(std::make_pair(-1, vec[i]));
  }
  return pairs;
}

std::vector<std::pair<int, int> > PmergeMe::mergeSortVec(std::vector<std::pair<int, int> > vec) {
  if (vec.size() < 2)
    return vec;
  int mid = vec.size() / 2;
  std::vector<std::pair<int, int> > lefthalf(vec.begin(), vec.begin() + mid);
  std::vector<std::pair<int, int> > righthalf(vec.begin() + mid, vec.end());
  // for example we have a vector = [(10,3), (5,7), (7, 6) (-1,4)]
  lefthalf = mergeSortVec(lefthalf); // merge: [(5,7), (10,3)]
  righthalf = mergeSortVec(righthalf);  // merge: [(7, 6), (-1,4)]
  std::vector<std::pair<int, int> > result;
  unsigned int i = 0, j = 0;
  while(i < lefthalf.size() && j < righthalf.size()) {
    if (comparePairs(lefthalf[i], righthalf[j])) {
      result.push_back(lefthalf[i]);
      i++;
    } else {
      result.push_back(righthalf[j]);
      j++;
    }
  }
  while (i < lefthalf.size()) {
    result.push_back(lefthalf[i]);
    i++;
  }
  while (j < righthalf.size()) {
    result.push_back(righthalf[j]);
    j++;
  }
  return result;
}

void PmergeMe::binaryInsertionSortVec(std::vector<std::pair<int, int> >& vec, int index) {
  int valueToInsert = vec[index].second;
  vec[index].second = -2;

  int start = 0;
  while (start < index) {
    int mid = start + (index - start) / 2;
    if (vec[mid].first < valueToInsert) {
      start = mid+1;
    } else {
      index = mid;
    }
  }
  vec.insert(vec.begin() + start, std::make_pair(valueToInsert, -1));
}

void PmergeMe::mergeInsertSortVec(std::vector<int>& vec) {
  if (vec.size() < 2)
    return ;
  std::vector<std::pair<int, int> > pairs = getPairsVec(vec);
  pairs = mergeSortVec(pairs);
  pairs.insert(pairs.begin(), std::make_pair(pairs[0].second, -1));
  pairs[1].second = -2;

  for (size_t i = 1; i < pairs.size(); i++) {
    if (pairs[i].second != -2)
      binaryInsertionSortVec(pairs, i);
  }
  if (pairs.back().first == -1)
    pairs.pop_back();
  vec.clear();
  for (size_t i = 0; i < pairs.size(); i++)
    vec.push_back(pairs[i].first);
}