#include "Page.hpp"

using std::string;
using std::vector;
using ariel::Direction;

vector<char> &Page::getRow(int row) {
    if (!_rows.contains(row)) {
        _rows[row] = vector<char>(rowLength, '_');
    }
    return _rows[row];
}

string Page::getSection(int row, int column, Direction direction, int str_len) {
    string section;
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            section.push_back(line.at(i));
        }
    } else if (direction == Direction::Vertical) {
        for (int i = row; i < (str_len + row); ++i) {
            auto &line = this->getRow(i);
            section.push_back(line.at(column));
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
            line.at(i + column) = str.at(i);
        }
    } else if (direction == Direction::Vertical) {
        for (int i = 0; i < str.size(); ++i) {
            auto &line = this->getRow(i + row);
            line.at(column) = str.at(i);
        }
    }
}

void Page::erase(int row, int column, ariel::Direction direction, int str_len) {
    if (direction == Direction::Horizontal) {
        auto &line = this->getRow(row);
        for (int i = column; i < (str_len + column); ++i) {
            line.at(i) = '~';
        }
    } else if (direction == Direction::Vertical) {
        for (int i = row; i < (str_len + row); ++i) {
            auto &line = this->getRow(i);
            line.at(column) = '~';
        }
    }
}

void Page::printPage() {
    int curr_row_num = 0;
    string str;
    str.append(rowLength, '_');
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
