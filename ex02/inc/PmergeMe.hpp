#ifndef PMERGEME_CLASS_H
# define PMERGEME_CLASS_H

# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>

# define VERBOSE false

template<typename T, template <typename, typename> class Container>
class PmergeMe {
public:
	PmergeMe<T, Container>(void);
	PmergeMe<T, Container>(const PmergeMe<T, Container> &src);
	~PmergeMe<T, Container>(void);
	PmergeMe<T, Container>	&operator =(const PmergeMe<T, Container> &src);

	Container<T, std::allocator<T> > sort(const Container<T, std::allocator<T> > &array) const;
};

# include "../src/PmergeMe.tpp"

#endif
