/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:59:39 by tfriedri          #+#    #+#             */
/*   Updated: 2023/09/18 15:22:53 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(int argc, char* argv[])
{
	if (argc < 2)
		throw std::invalid_argument("Error:\nPlease provide at least one argument.");
	for (int i = 1; i < argc; i++) {
		if (!containsOnlyDigits(argv[i]))
			throw std::invalid_argument("Error:\nArguments must be positive integers.");
		_vec.push_back(std::stoi(argv[i]));
		_lst.push_back(std::stoi(argv[i]));
	}
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
	std::cout << std::endl;
	clock_t start1 = clock();
	mergeInsertSortVec(_vec);
	clock_t end1 = clock();
	double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;
	clock_t start2 = clock();
	mergeInsertSortLst(_lst);
	clock_t end2 = clock();
	double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;
	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << _vec[i] << " ";
	std::cout << std::endl;
	std::cout << "Time for sorting as vector: " << time1 << "us" << std::endl;
	std::cout << "Time for sorting as list: " << time2 << "us" << std::endl;
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
	return ;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		this->_vec = rhs._vec;
		this->_lst = rhs._lst;
	}
	return (*this);
}

//--------------------MERGE INSERT GENERAL--------------------//

bool PmergeMe::containsOnlyDigits(const std::string& str) {
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!std::isdigit(*it))
            return false;
    }
    return true;
}

unsigned int PmergeMe::jacobsthal(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    return PmergeMe::jacobsthal(n-1) + 2*PmergeMe::jacobsthal(n-2);
}

bool PmergeMe::comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first == -1 && b.first != -1)
        return false;
    else if (a.first != -1 && b.first == -1)
        return true;
    else
        return a.first < b.first;
}

//--------------------MERGE INSERT VEC & LST--------------------//

size_t PmergeMe::getPairIndexVec(std::vector<std::pair<int, int> > vec, size_t index) {
    int i = 0;
    while (index > 1 || vec[i].second == -1) {
        if (vec[i].second != -1)
            index--;
        i++;
    }
    return i;
}

size_t PmergeMe::getPairIndexLst(std::list<std::pair<int, int> > lst, size_t index) {
	int i = 0;
	std::list<std::pair<int, int> >::iterator it = lst.begin();
	while (it != lst.end() && (index > 1 || it->second == -1)) {
		if (it->second != -1) {
			index--;
		}
		++it;
		++i;
	}
	return i;
}

std::vector<std::pair<int, int> > PmergeMe::getPairsVec(std::vector<int>& arr) {
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size() - 1; i += 2) {
        if (arr[i] < arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }
    for (size_t i = 0; i < arr.size(); i += 2) {
        if (i + 1 < arr.size())
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(-1, arr[i]));
    }
    return pairs;
}

std::list<std::pair<int, int> > PmergeMe::getPairsLst(std::list<int>& arr) {
	std::list<std::pair<int, int> > pairs;
	std::list<int>::iterator it = arr.begin();
	while (it != arr.end()) {
		int first = *it;
		++it;
		if (it != arr.end()) {
			int second = *it;
			++it;
			if (first < second) {
				std::swap(first, second);
			}
			pairs.push_back(std::make_pair(first, second));
		} else {
			pairs.push_back(std::make_pair(-1, first));
		}
	}
	return pairs;
}

std::vector<std::pair<int, int> > PmergeMe::mergeSortVec(std::vector<std::pair<int, int> > vec) {
    if (vec.size() < 2) {
        return vec;
    }
    int mid = vec.size() / 2;
    std::vector<std::pair<int, int> > lefthalf(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<int, int> > righthalf(vec.begin() + mid, vec.end());
    lefthalf = mergeSortVec(lefthalf);
    righthalf = mergeSortVec(righthalf);
    std::vector<std::pair<int, int> > result;
    unsigned i = 0;
    unsigned j = 0;
    while (i < lefthalf.size() && j < righthalf.size()) {
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

std::list<std::pair<int, int> > PmergeMe::mergeSortLst(std::list<std::pair<int, int> > lst) {
    if (lst.size() < 2) {
        return lst;
    }
    std::list<std::pair<int, int> > lefthalf;
    std::list<std::pair<int, int> > righthalf;
    std::list<std::pair<int, int> >::iterator it = lst.begin();
    int mid = lst.size() / 2;
    for (int i = 0; i < mid; ++i) {
        lefthalf.push_back(*it);
        ++it;
    }
    while (it != lst.end()) {
        righthalf.push_back(*it);
        ++it;
    }
    lefthalf = mergeSortLst(lefthalf);
    righthalf = mergeSortLst(righthalf);
    std::list<std::pair<int, int> > result;
    std::list<std::pair<int, int> >::iterator left_it = lefthalf.begin();
    std::list<std::pair<int, int> >::iterator right_it = righthalf.begin();
    while (left_it != lefthalf.end() && right_it != righthalf.end()) {
        if (comparePairs(*left_it, *right_it)) {
            result.push_back(*left_it);
            ++left_it;
        } else {
            result.push_back(*right_it);
            ++right_it;
        }
    }
    while (left_it != lefthalf.end()) {
        result.push_back(*left_it);
        ++left_it;
    }
    while (right_it != righthalf.end()) {
        result.push_back(*right_it);
        ++right_it;
    }
    return result;
}

void PmergeMe::binaryInsertionSortVec(std::vector<std::pair<int, int> >& vec, int index) {
    int valueToInsert = vec[index].second;
    vec[index].second = -2;
    int start = 0;
    while (start < index) {
        int mid = start + (index - start) / 2;
        if (vec[mid].first < valueToInsert)
            start = mid + 1;
        else
            index = mid;
    }
    vec.insert(vec.begin() + start, std::make_pair(valueToInsert, -1));
}

void PmergeMe::binaryInsertionSortLst(std::list<std::pair<int, int> >& lst, int index) {
	std::list<std::pair<int, int> >::iterator it = lst.begin();
	std::advance(it, index);
	int valueToInsert = it->second;
	it->second = -2;
	std::list<std::pair<int, int> >::iterator start = lst.begin();
	while (start != it) {
		std::list<std::pair<int, int> >::iterator mid = start;
		std::advance(mid, std::distance(start, it) / 2);
		if (mid->first < valueToInsert) {
			start = mid;
			++start;
		} else {
			it = mid;
		}
	}
	lst.insert(start, std::make_pair(valueToInsert, -1));
}

void PmergeMe::mergeInsertSortVec(std::vector<int>& vec) {
    if (vec.size() < 2)
        return;
    std::vector<std::pair<int, int> > pairs = getPairsVec(vec);
    pairs = mergeSortVec(pairs);
    size_t b_max = pairs.size();
    pairs.insert(pairs.begin(), std::make_pair(pairs[0].second, -1));
    pairs[1].second = -2;
    size_t  bx = 1;
    for(int jac_index = 2; bx < b_max; jac_index++){
        size_t old_jac = bx;
        bx = jacobsthal(jac_index);
        if (bx > b_max) bx = b_max;
        for (size_t rpts = bx - old_jac; rpts > 0; rpts--){
            binaryInsertionSortVec(pairs, getPairIndexVec(pairs, rpts + old_jac));
        }
    }
    if (pairs.back().first == -1)
        pairs.pop_back();
    vec.clear();
    for (size_t i = 0; i < pairs.size(); i++)
        vec.push_back(pairs[i].first);
}

void PmergeMe::mergeInsertSortLst(std::list<int>& lst) {
	if (lst.size() < 2)
		return;
	std::list<std::pair<int, int> > pairs = getPairsLst(lst);
	pairs = mergeSortLst(pairs);
	size_t b_max = pairs.size();
	int val = pairs.front().second;
	pairs.front().second = -2;
	pairs.insert(pairs.begin(), std::make_pair(val, -1));
	size_t bx = 1;
	for (int jac_index = 2; bx < b_max; jac_index++) {
		size_t old_jac = bx;
		bx = jacobsthal(jac_index);
		if (bx > b_max) bx = b_max;
		for (size_t rpts = bx - old_jac; rpts > 0; rpts--) {
			binaryInsertionSortLst(pairs, getPairIndexLst(pairs, rpts + old_jac));
		}
	}
	if (pairs.back().first == -1)
		pairs.pop_back();
	lst.clear();
	for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		lst.push_back(it->first);
}
