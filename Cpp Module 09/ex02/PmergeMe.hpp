#pragma once

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <list>

/*
*  1. Group elements into pairs
*   [3, 5, 9, 7, 4] -> [(3,5), (9,7), (4)]
*
*  2. Sort each pair internally
*   [(3,5), (7,9), (4)]
*
*  3. Create a sorted chain using larger numbers
*   Main chain: [5, 9]
*   Pending: [3, 7, 4]
*
*  4. Insert remaining elements using binary search
*   Insert 3 -> [3, 5, 9]
*   Insert 7 -> [3, 5, 7, 9]
*   Insert 4 -> [3, 4, 5, 7, 9]
*/

class PmergeMe {
  private:
    std::vector<int> _vec;
    std::list<int> _list;
  public:
    /* Constructors */
    PmergeMe();
    PmergeMe(int ac, char *av[]);
    PmergeMe(PmergeMe const & src);
    ~PmergeMe();

    /* Operator Overloads */
    PmergeMe & operator=(PmergeMe const & src);

    /* Public Methods */
    void mergeInsertSortVec(std::vector<int> & vec);
    void mergeInsertSortList(std::list<int> & list);

    protected:
      bool OnlyDigits(std::string const & str);
      int jacobsthal(int n);
      size_t getPairIndexVec(std::vector<std::pair<int, int> > vec, size_t index);
      std::vector<std::pair<int, int> > getPairsVec(std::vector<int>& vec);
      std::vector<std::pair<int, int> > mergeSortVec(std::vector<std::pair<int, int> > vec);
      bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b);
      void binaryInsertionSortVec(std::vector<std::pair<int, int> >& vec, int index);

      // print pairs
      void printPairs(std::vector<std::pair<int, int> > pairs);
};