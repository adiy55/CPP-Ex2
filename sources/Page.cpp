#include "Page.hpp"

using std::string;
using std::vector;
using ariel::Direction;

typedef unsigned int uint;

vector<char> &Page::getRow(int row) {
    if (!_rows.contains(row)) { // todo: change to count?
        _rows[row] = vector<char>(ROW_LENGTH, UNDERSCORE);
    }
    return _rows[row];
}

string Page::getSection(int row, int column, Direction direction, int str_len) {
    string section;
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            section.push_back(line.at(uint(i)));
        }
    } else if (direction == Direction::Vertical) {
        int length = str_len + row;
        for (int i = row; i < length; ++i) {
            auto &line = this->getRow(i);
            section.push_back(line.at(uint(column)));
        }
    }
    return section;
}

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

void Page::erase(int row, int column, ariel::Direction direction, int str_len) {
    string tilda_str;
    tilda_str.append(uint(str_len), TILDA);
    this->write(row, column, direction, tilda_str);
}

void Page::printPage() {
    int curr_row_num = 0;
    string str;
    str.append(ROW_LENGTH, UNDERSCORE);
    for (auto &[key, value]: _rows) {
        for (; curr_row_num < key; ++curr_row_num) {
            std::cout << str << '\n';
        }
        Page::printRow(value);
    }
}

void Page::printRow(vector<char> &row) {
    string curr_row = string(row.begin(), row.end());
    std::cout << curr_row << '\n';
}

void Page::checkValidForWrite(char curr_char, char new_char) {
    if (curr_char != UNDERSCORE && new_char != TILDA) {
        throw std::invalid_argument("Can not write over existing or erased text!");
    }
}
