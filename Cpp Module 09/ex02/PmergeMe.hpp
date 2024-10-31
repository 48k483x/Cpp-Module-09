#pragma once

# include <iostream>
# include <sstream>
# include <string>
# include <deque>
# include <vector>

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
    // Implement the class
  public:
    /* Constructors */
    PmergeMe();
    PmergeMe(PmergeMe const & src);
    ~PmergeMe();

    /* Operator Overloads */
    PmergeMe & operator=(PmergeMe const & src);

    /* Public Methods */
};