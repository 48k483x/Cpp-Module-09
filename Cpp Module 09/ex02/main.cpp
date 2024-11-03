# include "PmergeMe.hpp"

int main (int ac, char *av[]) {
  try {
    PmergeMe pmm(ac, av);
  } catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}