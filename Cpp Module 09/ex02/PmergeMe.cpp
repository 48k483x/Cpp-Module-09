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
}

bool PmergeMe::OnlyDigits(const std::string& str) {
  return str.find_first_not_of("0123456789") == std::string::npos;
}

bool PmergeMe::comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  if (a.first == -1 && b.first != -1) return false;  // Keep (a) after (b) if (a) has first element -1
  if (a.first != -1 && b.first == -1) return true;   // Keep (a) before (b) if (b) has first element -1
  return a.first < b.first;                          // Otherwise, compare normally by first element
}


// Jacobsthal Sequence Definition:
// The sequence starts with:
// J0 = 0          // The 0th term is 0
// J1 = 1          // The 1st term is 1
// For n ≥ 2, each term is defined as:
// Jn = Jn−1 + 2 * Jn−2  // The nth term is the sum of the previous term and twice the term before that
// This recursive relationship allows us to calculate any term in the Jacobsthal sequence.
int PmergeMe::jacobsthal(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return PmergeMe::jacobsthal(n - 1) + 2 * PmergeMe::jacobsthal(n - 2);
}

size_t PmergeMe::getPairIndexVec(std::vector<std::pair<int, int> > vec, size_t index) {
  size_t i = 0;
  while (index > 1 || vec[i].second == -1) {
    if (vec[i].second != -1)
      index--;
    i++;
  }
  return i;
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

std::vector<std::pair<int, int> > PmergeMe::mergeSortVec(std::vector<std::pair<int, int> > vec) {
  if (vec.size() < 2)
    return vec;
  int mid = vec.size() / 2;
  std::vector<std::pair<int, int> > lefthalf(vec.begin(), vec.begin() + mid);
  std::vector<std::pair<int, int> > righthalf(vec.begin() + mid, vec.end());
  lefthalf = mergeSortVec(lefthalf);
  righthalf = mergeSortVec(righthalf);
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

/*
  Suppose we have: [(3,-1), (7,-2), (9,4)]

  valueToInsert = 4
  vec[2].second = -2  // Mark original position as processed
  start = 0
  index = 2

Loop 1:
  mid = 0 + (2-0)/2 = 1
  Is vec[1].first (7) < 4? No
  So index = 1 (narrow search to left half)

Loop 2:
  mid = 0 + (1-0)/2 = 0
  Is vec[0].first (3) < 4? Yes
  So start = 0+1 = 1 (narrow search to right half)

  Loop ends since start (1) >= index (1)
  Insert 4 at position 1: [(3,-1), (4,-1), (7,-2), (9,-2)]
*/

void PmergeMe::binaryInsertionSortVec(std::vector<std::pair<int, int> >& vec, int index) {
  // printPairs(vec);
  int valueToInsert = vec[index].second;
  vec[index].second = -2;
  // printPairs(vec);

  int start = 0;
  while (start < index) {
    // std::cout << "start: " << start << " index: " << index << std::endl;
    int mid = start + (index - start) / 2;
    // std::cout << "mid: " << mid << std::endl;
    // std::cout << "vec[mid].first: " << vec[mid].first << " valueToInsert: " << valueToInsert << std::endl;
    if (vec[mid].first < valueToInsert) {
      start = mid+1;
    } else {
      index = mid;
    }
    // std::cout << "start: " << start << " index: " << index << std::endl;
    // std::cout << "----------------" << std::endl;
  }
  vec.insert(vec.begin() + start, std::make_pair(valueToInsert, -1));
}


void PmergeMe::mergeInsertSortVec(std::vector<int>& vec) {
  if (vec.size() < 2)
    return ;
  std::vector<std::pair<int, int> > pairs = getPairsVec(vec);
  // printPairs(pairs);
  pairs = mergeSortVec(pairs);
  // printPairs(pairs);
  pairs.insert(pairs.begin(), std::make_pair(pairs[0].second, -1));
  pairs[1].second = -2;

  for (size_t i = 1; i < pairs.size(); i++) {
    if (pairs[i].second != -2)
      binaryInsertionSortVec(pairs, i);
  }
  // printPairs(pairs);
  if (pairs.back().first == -1)
    pairs.pop_back();
  // printPairs(pairs);

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