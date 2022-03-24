#ifndef CPP_EX2_PAGE_HPP
#define CPP_EX2_PAGE_HPP

#include <map>
#include <vector>
#include <string>
#include "Direction.hpp"

#define rowLength 100
//const int rowLength = 100;

class Page {

private:

    std::map<int, std::vector<char>> _rows;

    std::vector<char> &getRow(int row);

public:

    std::string getSection(int row, int column, ariel::Direction direction, int str_len);

    void write(int row, int column, ariel::Direction direction, const std::string &str);

    void erase(int row, int column, ariel::Direction direction, int str_len);

};

#endif //CPP_EX2_PAGE_HPP
