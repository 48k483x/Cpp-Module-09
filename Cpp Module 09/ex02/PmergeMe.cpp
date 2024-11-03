# include "PmergeMe.hpp"

/* Constructors */
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const & src) { *this = src; }

PmergeMe::~PmergeMe() {}

/* Operator Overloads */
PmergeMe & PmergeMe::operator=(PmergeMe const & src) {
  if (this != &src) {
    _vec = src._vec;
    _list = src._list;
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

void PmergeMe::printPairs(std::vector<std::pair<int, int> > pairs) {
  for (size_t i = 0; i < pairs.size(); i++) {
    std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
  }
  std::cout << std::endl;
}