# include "BitcoinExchange.hpp"


/* Constructors */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src) {
  *this = src;
}

BitcoinExchange::~BitcoinExchange() {}

/* Operators */
BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & src) {
  if (this != &src) {
    *this = src;
  }
  return *this;
}

/* strtrim */
void BitcoinExchange::strtrim(std::string & str ) {
  size_t i = 0;
  size_t j = str.length() - 1;

  while (str[i] == ' ' || str[i] == '\t') i++;
  while (str[j] == ' ' || str[j] == '\t') j--;

  str = str.substr(i, j - i + 1);
}

/* isValide Date */
bool BitcoinExchange::isValideDate(std::string  & date) {
  int year, month, day;
  strtrim(date);
  if (date.find(' ') != std::string::npos) return false;
  if (date[4] != '-' || date[7] != '-') return false;
   // Extract parts
  std::string yearStr = date.substr(0, 4);
  std::string monthStr = date.substr(5, 2);
  std::string dayStr = date.substr(8, 2);

    // Convert to numbers
  year = atoi(yearStr.c_str());
  month = atoi(monthStr.c_str());
  day = atoi(dayStr.c_str());

  if (year < 2009 || year > 2022) return false;
  if (month < 1 || month > 12) return false;
  if (day < 1 || day > 31) return false;

  if (month == 2 && day > 29) return false;
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

  return true;
}

/* Parse data And Fill dataBase And input */
bool BitcoinExchange::parseData(char split, std::string const& line, std::pair<std::string, float> & data)
{
  std::stringstream ss(line);
  std::string date;
  std::string valueStr;
  char *endPtr;
  float value = 0;

  if (std::getline(ss, date, split)) {
    if (!isValideDate(date)) {
      std::cerr << "Error: bad input => ";
      std::cerr << date << std::endl;
      return false;
    }
    std::getline(ss, valueStr); // Read the entire remaining part of the line into valueStr
    strtrim(valueStr);
    if (valueStr.find(' ') != std::string::npos) {
      std::cerr << "Error: bad input => ";
      std::cerr << date << std::endl;
      return false;
    }
    value = std::strtof(valueStr.c_str(), &endPtr);
    if (*endPtr != '\0') {
      std::cerr << "Error: bad input => ";
      std::cerr << valueStr << std::endl;
      return false;
    }
    if (split == '|' && (value < 0 || value > 1000)) {
      if (value < 0) std::cerr << "Error: not a positive number." << std::endl;
      else  std::cerr << "Error: too large a number." << std::endl;
      return false;
    }
    if (ss.fail()) return false;
    data = std::make_pair(date, value);
  }
  return true;
}



/* Load database */
void BitcoinExchange::loadDatabase(std::string const & filename) {
  /* Open data.csv file */
  std::ifstream file(filename.c_str());

  /* Check if file is open */
  if (!file.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return ;
  }
  std::string line;
  std::getline(file, line);
  std::pair<std::string, float> data;
  while (std::getline(file, line)) {
    if (parseData(',', line, data)) {
      dataBase[data.first] = data.second;
    }
  }
  file.close();
}

/* Process Input File */
void BitcoinExchange::processInputFile(std::string const & filename) {
  /* Open data.csv file */
  std::ifstream file(filename.c_str());

  /* Check if file is open */
  if (!file.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return ;
  }
  std::string line;
  std::getline(file, line);
  if (line != "date | value") {
    std::cerr << "Error: invalid file format." << std::endl;
    return ;
  }
  std::pair<std::string, float> data;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    if (parseData('|', line, data)) {
      input[data.first] = data.second;
      std::cout << input.rbegin()->first << " => " << input.rbegin()->second;
      std::cout << " = " << getExchangeRate(input.rbegin()->first) * input.rbegin()->second << std::endl;
    }
    else continue;
  }
}

/* Find Correct Date */
float  BitcoinExchange::getExchangeRate(std::string const & date) {
  std::map<std::string, float>::iterator it = dataBase.find(date);

  if (it == dataBase.end()) {
    std::string closest = getClosestDate(date);
    return dataBase[closest];
  }
  return it->second;
}

/* Get Closest Date */
std::string BitcoinExchange::getClosestDate(std::string const & date) {
  std::map<std::string,float>::iterator it = dataBase.upper_bound(date);

  if (it == dataBase.begin()) return it->first;
  --it;
  return it->first;
}