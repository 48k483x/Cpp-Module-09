#pragma once

# include <iostream>
# include <stack>
# include <sstream>

class RPN {
  private:
    std::stack<int> _stack;
    int _upgradedResult;

  public:
  /* Constructors */
    RPN();
    RPN(RPN const & src);
    ~RPN();

  /* Operator Overloads */
    RPN & operator=(RPN const & src);

  /* Public Methods */
    void process(std::string expression); /* Process the RPN expression */

    bool isNum(std::string token); /* Check if the token is a number */

    bool isOperator(std::string token); /* Check if the token is an operator */

    int calculate(int a, int b, std::string token); /* Calculate the result of the operation */

    void _errorHandler(); /* Handle the error */
};