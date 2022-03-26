#ifndef CPP_EX2_PAGE_HPP
#define CPP_EX2_PAGE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Direction.hpp"

#define ROW_LENGTH 100
#define TILDA '~'
#define UNDERSCORE '_'

class Page {

private:

    std::map<int, std::vector<char>> _rows; // todo: check if map keeps order by ascending key

    std::vector<char> &getRow(int row);

    static void checkValidForWrite(char, char);

    static void printRow(std::vector<char> &row);

public:

    std::string getSection(int row, int column, ariel::Direction direction, int str_len);

    void write(int row, int column, ariel::Direction direction, const std::string &str);

    void erase(int row, int column, ariel::Direction direction, int str_len);

    void printPage();

};

#endif //CPP_EX2_PAGE_HPP
