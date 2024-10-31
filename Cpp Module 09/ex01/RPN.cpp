# include "RPN.hpp"

/* Constructors */
RPN::RPN() : _upgradedResult(0) {}

RPN::RPN(RPN const & src) { *this = src; }

RPN::~RPN() {}

/* Operator Overloads */
RPN & RPN::operator=(RPN const & src) {
  if (this != &src) {
    this->_stack = src._stack;
    this->_upgradedResult = src._upgradedResult;
  }
  return *this;
}

/* Public Methods */
void RPN::process(std::string expression) {
  /* ss is a stream that will be used to parse the expression */
  std::stringstream ss(expression);
  std::string token;
  /* While the stream is not empty, i parse the expression */
  while (ss >> token) {
    /* If the token is a number, i push it to the stack */
    if (isNum(token))  _stack.push(std::stoi(token));
    /* If the token is an operator, i calculate the result of the operation */
    else if (isOperator(token)) {
      /* If the stack has less than 2 elements, i return an error */
      if (_stack.size() < 2) return _errorHandler();
      /* i pop the last 2 elements of the stack */
      int a = _stack.top();
      _stack.pop();
      int b = _stack.top();
      _stack.pop();
      /* If the operator is a division and the second element is 0, i return an error */
      if (a == 0 && token == "/") return _errorHandler();
      /* i calculate the result of the operation and push it to the stack */
      _upgradedResult = calculate(b, a, token);
      _stack.push(_upgradedResult);
    } else return _errorHandler();
  }
  /* If the stack has more than 1 element, i return an error */
  if (_stack.size() != 1) return _errorHandler();
  /* print the result */
  std::cout << _stack.top() << std::endl;
}


/* isNum, Check if the token is a number */
bool RPN::isNum(std::string token) {
  if (token.find_first_not_of("0123456789") == std::string::npos)
    if (std::stoi(token) <= 9 || std::stoi(token) >= 0) return true;
  return false;
}


/* isOperator, Check if the token is an operator */
bool RPN::isOperator(std::string token) {
  return (token == "+" || token == "-" || token == "*" || token == "/");
}


/* calculate, Calculate the result of the operation */
int RPN::calculate(int a, int b, std::string token) {
  if (token == "+") return a + b;
  if (token == "-") return a - b;
  if (token == "*") return a * b;
  if (token == "/") return a / b;
  return 0;
}


/* _errorHandler, Handle the error */
void RPN::_errorHandler() {
  std::cerr << "Error" << std::endl;
  return ;
}