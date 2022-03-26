#ifndef CPP_EX2_PAGE_HPP
#define CPP_EX2_PAGE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Direction.hpp"

/*
 * Defined macros for vital values in the assignment.
 * Advantages of this approach:
 * Global (not scope controlled) and does not require memory allocation (pre-processor runs before the compiler).
 */
#define ROW_LENGTH 100
#define TILDA '~'
#define UNDERSCORE '_'

/*
 * OOP approach -> Page object allows easier functionality in Notebook class.
 */
class Page {

private:

    /*
     * Map: unique keys, typically a red-black tree,
     * sorted by increasing order of keys - this is handy for printing a whole page
     * Additional information: https://en.cppreference.com/w/cpp/container/map
     */
    std::map<int, std::vector<char>> _rows;

    std::vector<char> &getRow(int row);

    static void checkValidForWrite(char, char);

    static void printRow(const std::vector<char> &row);

public:

    std::string getSection(int row, int column, ariel::Direction direction, int str_len);

    void write(int row, int column, ariel::Direction direction, const std::string &str);

    void erase(int row, int column, ariel::Direction direction, int str_len);

    void printPage() const;

};

#endif //CPP_EX2_PAGE_HPP
