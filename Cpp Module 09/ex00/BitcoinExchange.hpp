#pragma once

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>
# include <functional>
# include <iomanip>
# include <sstream>
# include <cmath>
# include <limits>
# include <stdexcept>
# include <fstream>

class BitcoinExchange{
  private:
    std::map<std::string, float> dataBase;
    std::map<std::string, float> input;

  public:
  /* Constructors */
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const & src);
    ~BitcoinExchange();

  /* Operators */
    BitcoinExchange & operator=(BitcoinExchange const & src);


  /* strtrim */
    void strtrim(std::string & str);

  /* isValide Date */
    bool isValideDate(std::string  &date);

  /* Parse data And Fill dataBase And input */
    bool parseData(char split, std::string const& line, std::pair<std::string, float> & data);

  /* Load database */
    void loadDatabase(std::string const & filename);

  /* Process Input File */
    void processInputFile(std::string const & filename);

  /* Print Data */
  float getExchangeRate(std::string const & date);

  /* Get Closest Date */
  std::string getClosestDate(std::string const & date);
};