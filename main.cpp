#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

public:
    void parse(int argc, char** argv) {
        for (int i = 1; i < argc; ++i) {
            int num = std::stoi(argv[i]);
            _vec.push_back(num);
            _deq.push_back(num);
        }
    }

    void sort() {
        // Display before sorting
        std::cout << "Before: ";
        for (int num : _vec) std::cout << num << " ";
        std::cout << std::endl;

        // Sort vector
        auto start_vec = std::chrono::high_resolution_clock::now();
        std::sort(_vec.begin(), _vec.end());
        auto end_vec = std::chrono::high_resolution_clock::now();
        auto vec_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_vec - start_vec);

        // Sort deque
        auto start_deq = std::chrono::high_resolution_clock::now();
        std::sort(_deq.begin(), _deq.end());
        auto end_deq = std::chrono::high_resolution_clock::now();
        auto deq_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_deq - start_deq);

        // Display after sorting
        std::cout << "After: ";
        for (int num : _vec) std::cout << num << " ";
        std::cout << std::endl;

        // Display times
        std::cout << "Time to process a range of " << _vec.size()
                  << " elements with std::vector : " << vec_duration.count() << " us" << std::endl;
        std::cout << "Time to process a range of " << _deq.size()
                  << " elements with std::deque : " << deq_duration.count() << " us" << std::endl;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <positive integers>" << std::endl;
        return 1;
    }

    try {
        PmergeMe sorter;
        sorter.parse(argc, argv);
        sorter.sort();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}