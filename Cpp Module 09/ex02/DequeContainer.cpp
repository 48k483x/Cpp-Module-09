# include "PmergeMe.hpp"

std::deque<std::pair<int, int> > PmergeMe::getPairsDeq(std::deque<int>& list) {
  std::deque<std::pair<int, int> > pairs;
  /* Sort each pair internally (larger number becomes first)*/
  for (size_t i = 0; i < list.size() - 1; i += 2) {
    if (list[i] < list[i + 1])
      std::swap(list[i], list[i + 1]);
  }
  /* crete pairs, handling odd length arrays */
  for (size_t i = 0; i < list.size(); i += 2) {
    if (i + 1 < list.size())
      pairs.push_back(std::make_pair(list[i], list[i + 1]));
    else
      pairs.push_back(std::make_pair(-1, list[i]));
  }
  return pairs;
}

std::deque<std::pair<int, int> > PmergeMe::mergeSortDeq(std::deque<std::pair<int, int> > list) {
  if (list.size() < 2)
    return list;
  int mid = list.size() / 2;
  std::deque<std::pair<int, int> > lefthalf(list.begin(), list.begin() + mid);
  std::deque<std::pair<int, int> > righthalf(list.begin() + mid, list.end());
  lefthalf = mergeSortDeq(lefthalf);
  righthalf = mergeSortDeq(righthalf);
  std::deque<std::pair<int, int> > result;
  unsigned int i = 0, j = 0;

  while (i < lefthalf.size() && j < righthalf.size()) {
    if (comparePairs(lefthalf[i], righthalf[i])) {
      result.push_back(lefthalf[i]);
      i++;
    }
    else {
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

void PmergeMe::binaryInsertionSortDeq(std::deque<std::pair<int, int> >& vec, int index) {
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

void PmergeMe::mergeInsertSortDeq(std::deque<int>& vec) {
  if (vec.size() < 2)
    return ;
  std::deque<std::pair<int, int> > pairs = getPairsDeq(vec);
  pairs = mergeSortDeq(pairs);
  pairs.insert(pairs.begin(), std::make_pair(pairs[0].second, -1));
  pairs[1].second = -2;

  for (size_t i = 1; i < pairs.size(); i++) {
    if (pairs[i].second!= -2)
      binaryInsertionSortDeq(pairs, i);
  }
  if (pairs.back().first == -1)
    pairs.pop_back();
  vec.clear();
  for (size_t i = 0; i < pairs.size(); i++)
    vec.push_back(pairs[i].first);
}