/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:50:14 by tfriedri          #+#    #+#             */
/*   Updated: 2023/09/18 14:56:58 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::list<int> _lst;
	public:
		PmergeMe();
		PmergeMe(int argc, char* argv[]);
		~PmergeMe(void);
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &rhs);
		void mergeInsertSortVec(std::vector<int> &vec);
		void mergeInsertSortLst(std::list<int> &lst);
	protected:
		bool containsOnlyDigits(const std::string& str);
		unsigned int jacobsthal(int n);
		bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b);
		size_t getPairIndexVec(std::vector<std::pair<int, int> > vec, size_t index);
		size_t getPairIndexLst(std::list<std::pair<int, int> > lst, size_t index);
		std::vector<std::pair<int, int> > getPairsVec(std::vector<int>& arr);
		std::list<std::pair<int, int> > getPairsLst(std::list<int>& lst);
		std::vector<std::pair<int, int> > mergeSortVec(std::vector<std::pair<int, int> > vec);
		std::list<std::pair<int, int> > mergeSortLst(std::list<std::pair<int, int> > lst);
		void binaryInsertionSortVec(std::vector<std::pair<int, int> >& vec, int index);
		void binaryInsertionSortLst(std::list<std::pair<int, int> >& lst, int index);
};

#endif