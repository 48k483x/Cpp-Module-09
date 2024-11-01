#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include <climits>
#include <cstdlib>
#include <sys/time.h>

class PmergeMe
{
    private:
        std::vector<int> _C1;
        std::deque<int> _C2;

    public:
        //canonical form
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();

        //Helper methods
        void parse(int argNumber, char **arguments);
        int validNumber(std::string str);
        int jacobLadderSequence(int n);

        //Vector methods
        std::vector<int> sortedVector();
        void recursiveSortingVector(std::vector<std::pair<int, int> > &couple);
        void mergeSortVector(std::vector<std::pair<int, int> > &couple, int left, int right);
        void mergeVector(std::vector<std::pair<int, int> > &arr, int left, int mid, int right);
        std::vector<unsigned long> jacobLadderIndex(std::vector<int> &jacobSea, int size);

        //Deque methods
        std::deque<int> sortedDeque();
        void recursiveSortingDeque(std::deque<std::pair<int, int> > &couple);
        void mergeSortDeque(std::deque<std::pair<int, int> > &couple, int left, int right);
        void mergeDeque(std::deque<std::pair<int, int> > &arr, int left, int mid, int right);
        std::deque<unsigned long> jacobLadderIndex(std::deque<int> &jacobSea, int size);
};

template <typename T> void display(T &container)
{
    for (typename T::iterator it = container.begin(); it != container.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename container_type > int findIndex(container_type &container, int value)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        if (container[i] >= value && container[i -1 ] && container[i - 1] < value)
            return i + 1;
    }
    return -1;
}

#endif