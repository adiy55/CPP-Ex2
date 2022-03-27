#include "Page.hpp"

using std::string;
using std::vector;
using std::cout;
using std::invalid_argument;
using ariel::Direction;

typedef unsigned int uint; // assigns an alias to an existing datatype (more readable code)
// C++ type casting: https://stackoverflow.com/questions/103512/why-use-static-castintx-instead-of-intx

/**
 * If row does not exists- initializes a vector of underscores.
 * @param row number of the row
 * @return reference to the row
 */
vector<char> &Page::getRow(int row) {
    if (!_rows.contains(row)) { // todo: change to count?
        _rows[row] = vector<char>(ROW_LENGTH, UNDERSCORE); // initializes vector of size row_length with underscores
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
            section.push_back(line.at(static_cast<uint>(i)));
        }
    } else if (direction == Direction::Vertical) {
        int length = str_len + row;
        for (int i = row; i < length; ++i) {
            vector<char> &line = this->getRow(i);
            section.push_back(line.at(static_cast<uint>(column)));
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
            char &curr_char = line.at(static_cast<uint>(i + column));
            char new_char = str.at(static_cast<uint>(i));
            checkValidForWrite(curr_char, new_char); // helper function
            curr_char = new_char;
        }
    } else if (direction == Direction::Vertical) {
        for (int i = 0; i < str.size(); ++i) {
            vector<char> &line = this->getRow(i + row);
            char &curr_char = line.at(static_cast<uint>(column));
            char new_char = str.at(static_cast<uint>(i));
            checkValidForWrite(curr_char, new_char); // helper function
            curr_char = new_char;
        }
    }
}

/**
 * Marks over a specific part of the page.
 * @param str_len number of chars to erase
 */
/*
 * This method calls the write method (implemented above) to mark over the section.
 */
void Page::erase(int row, int column, ariel::Direction direction, int str_len) {
    string tilda_str;
    tilda_str.append(static_cast<uint>(str_len), TILDA); // appends tilda str_len times
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
    str.append(ROW_LENGTH, UNDERSCORE); // appends underscore row_length (100) times
    for (const auto &[key, value]: _rows) {
        for (; curr_row_num < key; ++curr_row_num) { // prints line of underscores if row (in between) does not exist
            cout << str << '\n'; // todo: necessary?
        }
        Page::printRow(value); // helper function
    }
}

/**
 * Prints a given row.
 * @param row const reference (type: vector<char>)
 */
void Page::printRow(const vector<char> &row) {
    string curr_row = string(row.begin(), row.end()); // using the string constructor:
    // accepts iterators to first and last position of the vector
    cout << curr_row << '\n';
}

/**
 * Checks if the place of the next character to write is valid.
 * @param curr_char char to overwrite
 * @param new_char char to write
 */
void Page::checkValidForWrite(char curr_char, char new_char) {
    if (curr_char != UNDERSCORE && new_char != TILDA) {
        throw invalid_argument("Can not write over existing or erased text!");
    }
}
