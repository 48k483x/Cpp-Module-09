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