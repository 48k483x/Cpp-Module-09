#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &src)
{
    *this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    (void)src;
    return *this;
}

PmergeMe::~PmergeMe(){}

// initial function for warming up the program
int PmergeMe::validNumber(std::string str)
{
    double number;
    std::stringstream ss;

    ss << str;
    ss >> number;
    if (number > INT_MAX)
        throw std::runtime_error("Number too big");
    return number;
}


// check if the container is sorted using one them (vector or deque) cuz they have the same values
bool isContainerSorted(std::vector<int> &container)
{
    for (size_t i = 0; i < container.size() - 1; i++)
    {
        if (container[i] > container[i + 1])
            return false;
    }
    return true;
}

// parse the arguments and store them in the two containers
void PmergeMe::parse(int argNumber, char **arguments)
{
    int number;
    std::stringstream ss;
    std::string str;

    
    for (int i = 0; i < argNumber; i++)
        ss << arguments[i] << " ";
    
    while (ss >> str)
    {
        if (str.empty() || str.find_first_not_of("0123456789") != std::string::npos)
        {
            if (!str.empty() && !(str[0] == '+' && (str).find_first_not_of("0123456789", 1) == std::string::npos))
                throw std::runtime_error("Invalid argument");
        }

        number = validNumber(str);
        _C1.push_back(number);
        _C2.push_back(number);

    }
    if (isContainerSorted(_C1))
        throw std::runtime_error("Already sorted");

    std::cout << "Before: ";
    for (size_t i = 0; i < _C1.size(); i++)
        std::cout << _C1[i] << " ";
    std::cout << std::endl;
}

// Jacob's ladder function to calculate the number of steps to reach the top of the ladder with n steps
/*
    * 1. if n = 0, return 0
    * 2. if n = 1, return 1
    * 3. return the sum of the previous two steps
*/
int PmergeMe::jacobLadderSequence(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobLadderSequence(n - 1) + 2 * jacobLadderSequence(n - 2);
}

// The beginning of the merge sort algorithm
// Starting by implementing main merge sort functions

// vector side

void PmergeMe::mergeVector(std::vector<std::pair<int, int> > &arr, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<std::pair<int, int> > L(n1), R(n2);

    for (i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    
    for (j = 0; j < n2; j++) 
        R[j] = arr[middle + 1 + j];

    i = j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].first <= R[j].first)
            arr[k++] = L[i++];
        else 
            arr[k++] = R[j++];
    }

    while (i < n1) 
        arr[k++] = L[i++];

    while (j < n2) 
        arr[k++] = R[j++];
}  

void PmergeMe::mergeSortVector(std::vector<std::pair<int, int> > &couple, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSortVector(couple, left, middle);
        mergeSortVector(couple, middle + 1, right);
        mergeVector(couple, left, middle, right);
    }
}
void PmergeMe::recursiveSortingVector(std::vector<std::pair<int, int> > &couple)
{
    for (size_t i = 0; i < couple.size(); i++)
    {
        if (couple[i].first < couple[i].second)
            std::swap(couple[i].first, couple[i].second);
    }
    mergeSortVector(couple, 0, couple.size() - 1);
}

// Jacob's ladder index function to calculate the index of the jacob's ladder function for a given size
std::vector<unsigned long> PmergeMe::jacobLadderIndex(std::vector<int> &jacobSea, int size)
{
    std::vector<unsigned long> jacobSeaIndex;
    int jacob = 0;

    for (size_t i = 0; i < jacobSea.size(); i++)
    {
        jacob = jacobSea[i];
        if (jacob <= size)
            jacobSeaIndex.push_back(jacob);

        while (jacob > 0 && jacobSea[i] != 1 && std::find(jacobSeaIndex.begin(), jacobSeaIndex.end(), --jacob) == jacobSeaIndex.end())
        {
            if (jacob > size)
                continue;
            jacobSeaIndex.push_back(jacob);
        }
    }
    jacobSeaIndex.erase(jacobSeaIndex.begin());
    return jacobSeaIndex;
}

std::vector<int> PmergeMe::sortedVector()
{    
    std::vector<std::pair<int, int> > couples;
    std::vector<int> strugle;
    
    if (_C1.size() % 2 != 0)
    {
        strugle.push_back(_C1.back());
        _C1.pop_back();
    }

    //spliting into couples
    for (size_t i = 0; i < _C1.size(); i += 2)
        couples.push_back(std::make_pair(_C1[i], _C1[i + 1]));

    //sorting couples
    recursiveSortingVector(couples);

    std::vector<int> smallest;
    std::vector<int> biggest;

    for (size_t i = 0; i < couples.size(); i++)
    {
        smallest.push_back(couples[i].second);
        biggest.push_back(couples[i].first);
    }
    // display(biggest);
    // display(smallest);

    if (smallest.size() >= 2)
    {
        std::vector<int> jacobSea;
        std::vector<unsigned long> jacobSeaIndex;
        unsigned long jacob = 0;

        // calculating the jacob's ladder index for the smallest vector 
        for (size_t i = 2; i < smallest.size() + biggest.size(); i++)
        {
            jacob = jacobLadderSequence(i);
            if (jacob > smallest.size())
            {
                jacobSea.push_back(jacob);
                break;
            }
            jacobSea.push_back(jacob);
        }
        jacobSeaIndex = jacobLadderIndex(jacobSea, smallest.size());
        
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), smallest[0]), smallest[0]);

        int sizeFinal = 0;
        for (size_t i = 0; i < jacobSeaIndex.size(); i++)
        {
            if (jacobSeaIndex[i] <= smallest.size())
            {
                if(pow(2, findIndex(jacobSea,jacobSeaIndex[i])) - 1 < biggest.size())
                    sizeFinal = pow(2, findIndex(jacobSea,jacobSeaIndex[i])) - 1;
                else
                    sizeFinal = biggest.size();
                
                biggest.insert(std::lower_bound(biggest.begin(), biggest.begin() + sizeFinal, smallest[jacobSeaIndex[i] - 1]), smallest[jacobSeaIndex[i] - 1]);
            }
            // std::cout << "jacobSeaIndex[" << i << "] = " << jacobSeaIndex[i] << std::endl;
        }
        //std::cout << "sizeFinal = " << sizeFinal << std::endl;
    }
    else
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), smallest[0]), smallest[0]);
    
    if (!strugle.empty())
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), strugle[0]), strugle[0]);

    return biggest;
}


// deque side
std::deque<int> PmergeMe::sortedDeque()
{
    std::deque<std::pair<int, int> > couples;
    std::deque<int> strugle;

    if (_C2.size() % 2 != 0)
    {
        strugle.push_back(_C2.back());
        _C2.pop_back();
    }

    //spliting into couples
    for (size_t i = 0; i < _C2.size(); i += 2)
        couples.push_back(std::make_pair(_C2[i], _C2[i + 1]));
    
    //sorting couples
    recursiveSortingDeque(couples);

    std::deque<int> smallest;
    std::deque<int> biggest;

    for (size_t i = 0; i < couples.size(); i++)
    {
        smallest.push_back(couples[i].second);
        biggest.push_back(couples[i].first);
    }

    if (smallest.size() >= 2)
    {
        std::deque<int> jacobSea;
        std::deque<unsigned long> jacobSeaIndex;
        unsigned long jacob = 0;

        // calculating the jacob's ladder index for the smallest vector 
        for (size_t i = 2; i < smallest.size() + biggest.size(); i++)
        {
            jacob = jacobLadderSequence(i);
            if (jacob > smallest.size())
            {
                jacobSea.push_back(jacob);
                break;
            }
            jacobSea.push_back(jacob);
        }
        jacobSeaIndex = jacobLadderIndex(jacobSea, smallest.size());
        
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), smallest[0]), smallest[0]);

        int sizeFinal = 0;
        for (size_t i = 0; i < jacobSeaIndex.size(); i++)
        {
            if (jacobSeaIndex[i] <= smallest.size())
            {
                if(pow(2, findIndex(jacobSea,jacobSeaIndex[i])) - 1 < biggest.size())
                    sizeFinal = pow(2, findIndex(jacobSea,jacobSeaIndex[i])) - 1;
                else
                    sizeFinal = biggest.size();
                
                biggest.insert(std::lower_bound(biggest.begin(), biggest.begin() + sizeFinal, smallest[jacobSeaIndex[i] - 1]), smallest[jacobSeaIndex[i] - 1]);
            }
        }
    }
    else
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), smallest[0]), smallest[0]);

    if (!strugle.empty())
        biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), strugle[0]), strugle[0]);

    return biggest;
}

void PmergeMe::recursiveSortingDeque(std::deque<std::pair<int, int> > &couple)
{
    for (size_t i = 0; i < couple.size(); i++)
    {
        if (couple[i].first < couple[i].second)
            std::swap(couple[i].first, couple[i].second);
    }
    mergeSortDeque(couple, 0, couple.size() - 1);
}

void  PmergeMe::mergeSortDeque(std::deque<std::pair<int, int> > &couple, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSortDeque(couple, left, middle);
        mergeSortDeque(couple, middle + 1, right);
        mergeDeque(couple, left, middle, right);
    }
}

void PmergeMe::mergeDeque(std::deque<std::pair<int, int> > &arr, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::deque<std::pair<int, int> > L(n1), R(n2);

    for (i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    
    for (j = 0; j < n2; j++) 
        R[j] = arr[middle + 1 + j];

    i = j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].first <= R[j].first)
            arr[k++] = L[i++];
        else 
            arr[k++] = R[j++];
    }

    while (i < n1) 
        arr[k++] = L[i++];

    while (j < n2) 
        arr[k++] = R[j++];
}

std::deque<unsigned long> PmergeMe::jacobLadderIndex(std::deque<int> &jacobSea, int size)
{
    std::deque<unsigned long> jacobSeaIndex;
    int jacob = 0;

    for (size_t i = 0; i < jacobSea.size(); i++)
    {
        jacob = jacobSea[i];
        if (jacob <= size)
            jacobSeaIndex.push_back(jacob);

        while (jacob > 0 && jacobSea[i] != 1 && std::find(jacobSeaIndex.begin(), jacobSeaIndex.end(), --jacob) == jacobSeaIndex.end())
        {
            if (jacob > size)
                continue;
            jacobSeaIndex.push_back(jacob);
        }
    }
    jacobSeaIndex.erase(jacobSeaIndex.begin());
    return jacobSeaIndex;
}
