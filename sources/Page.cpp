#include "Page.hpp"

using std::string;
using std::vector;
using ariel::Direction;

typedef unsigned int uint; // assign a shorter name to an existing datatype (more readable code)

/**
 * If row does not exists- initializes a vector of underscores.
 * @param row number of the row
 * @return reference to the row
 */
vector<char> &Page::getRow(int row) {
    if (!_rows.contains(row)) { // todo: change to count?
        _rows[row] = vector<char>(ROW_LENGTH, UNDERSCORE);
    }
    return _rows[row];
}

/**
 * Get a specific part of the text on the page.
 * @param str_len number of chars to get
 * @return string of the requested length
 */
string Page::getSection(int row, int column, Direction direction, int str_len) {
    string section;
    if (direction == Direction::Horizontal) {
        vector<char> &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            section.push_back(line.at(uint(i)));
        }
    } else if (direction == Direction::Vertical) {
        int length = str_len + row;
        for (int i = row; i < length; ++i) {
            vector<char> &line = this->getRow(i);
            section.push_back(line.at(uint(column)));
        }
    }
    return section;
}

/**
 * Write on a specific part of the page.
 * Throws exception if trying to write over written or erased text.
 * @param str text to write
 */
void Page::write(int row, int column, Direction direction, const string &str) {
    if (direction == Direction::Horizontal) {
        vector<char> &line = this->getRow(row);
        for (int i = 0; i < str.size(); ++i) {
            char &curr_char = line.at(uint(i + column));
            char new_char = str.at(uint(i));
            checkValidForWrite(curr_char, new_char);
            curr_char = new_char;
        }
    } else if (direction == Direction::Vertical) {
        for (int i = 0; i < str.size(); ++i) {
            vector<char> &line = this->getRow(i + row);
            char &curr_char = line.at(uint(column));
            char new_char = str.at(uint(i));
            checkValidForWrite(curr_char, new_char);
            curr_char = new_char;
        }
    }
}

/**
 * Erases a specific part on the page.
 * @param str_len number of chars to erase
 */
/*
 * This method calls the write method (implemented above) to mark over the section.
 */
void Page::erase(int row, int column, ariel::Direction direction, int str_len) {
    string tilda_str;
    tilda_str.append(uint(str_len), TILDA);
    this->write(row, column, direction, tilda_str);
}

/**
 * Prints the page. Prints a line of underscores if the line is empty.
 */
/*
 * The loop uses structured bindings (since C++17).
 * This allows to easily unpack key and value references in the map.
 * auto keyword detects the variable type: "The referenced type for the i-th identifier is std::tuple_element<i, E>::type"
 * Additional information: https://en.cppreference.com/w/cpp/language/structured_binding
 */
void Page::printPage() const {
    int curr_row_num = 0;
    string str;
    str.append(ROW_LENGTH, UNDERSCORE);
    for (auto &[key, value]: _rows) { //
        for (; curr_row_num < key; ++curr_row_num) {
            std::cout << str << '\n';
        }
        Page::printRow(value); // static helper function
    }
}

/**
 * Prints a given row.
 * @param row const reference (type: vector<char>)
 */
void Page::printRow(const vector<char> &row) {
    string curr_row = string(row.begin(), row.end());
    std::cout << curr_row << '\n';
}

/**
 * Checks if the place next character to write is valid.
 * @param curr_char char to overwrite
 * @param new_char char to be written
 */
void Page::checkValidForWrite(char curr_char, char new_char) {
    if (curr_char != UNDERSCORE && new_char != TILDA) {
        throw std::invalid_argument("Can not write over existing or erased text!");
    }
}
