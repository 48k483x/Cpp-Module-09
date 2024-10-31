# include "RPN.hpp"

int main ( int ac, char *av[]) {
  if (ac != 2) {
    std::cout << "Usage: ./RPN [expression]" << std::endl;
    return 1;
  }
  std::string expression = av[1];
  if (expression.empty()) {
    std::cout << "Error: Empty expression" << std::endl;
    return 1;
  }
  RPN rpn;
  rpn.process(expression);
}