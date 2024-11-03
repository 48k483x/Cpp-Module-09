# include "PmergeMe.hpp"

/* Constructors */
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const & src) { *this = src; }

PmergeMe::~PmergeMe() {}

/* Operator Overloads */
PmergeMe & PmergeMe::operator=(PmergeMe const & src) {
  if (this != &src) {
    // Implement the assignment operator
  }
  return *this;
}

/* Public Methods */
PmergeMe::PmergeMe(int ac, char *av[]) {
  /* Check for arguments */
  if (ac < 2)  throw std::invalid_argument("No arguments provided");
  for (int i = 1; i < ac; i++) {
    if (!OnlyDigits(av[i])) throw std::invalid_argument("Invalid argument");
    _vec.push_back(std::stoi(av[i]));
    _list.push_back(std::stoi(av[i]));
  }
  std::cout << "Before: ";
  /* Print the vector */
  for (size_t i = 0; i < _vec.size(); i++)
    std::cout << _vec[i] << " ";
  std::cout << std::endl;
  clock_t start = clock();
  mergeInsertSortVec(_vec);
  clock_t end = clock();
  double time1 = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
  /* Print the list */
  std::cout << "After: ";
  for (size_t i = 0; i < _vec.size(); i++)
    std::cout << _vec[i] << " ";
  std::cout << std::endl;
	std::cout << "Time for sorting as vector: " << time1 << "us" << std::endl;

  /* deque */
  start = clock();
  mergeInsertSortDeq(_list);
  end = clock();
  double time2 = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
  std::cout << "Time for sorting as deque: " << time2 << "us" << std::endl;

}

bool PmergeMe::OnlyDigits(const std::string& str) {
  return str.find_first_not_of("0123456789") == std::string::npos;
}

bool PmergeMe::comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  if (a.first == -1 && b.first != -1) return false;  // Keep (a) after (b) if (a) has first element -1
  if (a.first != -1 && b.first == -1) return true;   // Keep (a) before (b) if (b) has first element -1
  return a.first < b.first;                          // Otherwise, compare normally by first element
}

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

void PmergeMe::printPairs(std::vector<std::pair<int, int> > pairs) {
  for (size_t i = 0; i < pairs.size(); i++) {
    std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
  }
  std::cout << std::endl;
}