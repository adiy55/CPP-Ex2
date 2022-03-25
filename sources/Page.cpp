#include "Page.hpp"

using std::string;
using std::vector;
using ariel::Direction;

typedef unsigned int uint;

vector<char> &Page::getRow(int row) {
    if (!_rows.contains(row)) {
        _rows[row] = vector<char>(ROW_LENGTH, '_');
    }
    return _rows[row];
}

string Page::getSection(int row, int column, Direction direction, int str_len) {
    string section;
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            section.push_back(line.at(static_cast<uint>(i)));
        }
    } else if (direction == Direction::Vertical) {
        for (int i = row; i < (str_len + row); ++i) {
            auto &line = this->getRow(i);
            section.push_back(line.at(static_cast<uint>(column)));
            if (i < (str_len + row - 1)) {
                section.push_back('\n');
            }
        }
    }
    return section;
}

void Page::write(int row, int column, Direction direction, const string &str) {
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = 0; i < str.size(); ++i) {
            line.at(static_cast<uint>(i + column)) = str.at(static_cast<uint>(i));
        }
    } else if (direction == Direction::Vertical) {
        for (int i = 0; i < str.size(); ++i) {
            auto &line = this->getRow(i + row);
            line.at(static_cast<uint>(column)) = str.at(static_cast<uint>(i));
        }
    }
}

void Page::erase(int row, int column, ariel::Direction direction, int str_len) {
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            line.at(static_cast<uint>(i)) = TILDA;
        }
    } else if (direction == Direction::Vertical) {
        for (int i = row; i < (str_len + row); ++i) {
            auto &line = this->getRow(i);
            line.at(static_cast<uint>(column)) = TILDA;
        }
    }
}

void Page::printPage() {
    int curr_row_num = 0;
    string str;
    str.append(ROW_LENGTH, '_');
    for (auto &[key, value]: _rows) {
        for (; curr_row_num < key; ++curr_row_num) {
            std::cout << str << '\n';
        }
        Page::printRow(value);
    }
}

void Page::printRow(vector<char> &row) {
    for (char c: row) {
        std::cout << c;
    }
    std::cout << '\n';
}
