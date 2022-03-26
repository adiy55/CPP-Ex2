#include "Notebook.hpp"

using std::string;
using std::isprint;
using std::isspace;
using std::invalid_argument;
using std::out_of_range;

namespace ariel {

    void Notebook::write(int page_number, int row, int column, Direction direction, const string &str) {
        validateIntegers(page_number, row, column, direction);
        checkPrintable(str);
        Page &page = this->getPage(page_number);
        page.write(row, column, direction, str);
    }

    string Notebook::read(int page_number, int row, int column, Direction direction, int str_len) {
        validateIntegers(page_number, row, column, direction, str_len);
        Page &page = this->getPage(page_number);
        return page.getSection(row, column, direction, str_len);
    }

    void Notebook::erase(int page_number, int row, int column, Direction direction, int str_len) {
        validateIntegers(page_number, row, column, direction, str_len);
        Page &page = this->getPage(page_number);
        page.erase(row, column, direction, str_len);
    }

    void Notebook::show(int page_number) {
        validateIntegers({page_number});
        Page &page = this->getPage(page_number);
        page.printPage();
    }

    Page &Notebook::getPage(int page) {
        if (!_notebook.contains(page)) {
            _notebook[page] = Page();
        }
        return _notebook[page];
    }

    void Notebook::validateIntegers(int page_number, int row, int column, Direction direction, int str_len) {
        validateIntegers({page_number, row, column, str_len});
        if ((column >= ROW_LENGTH) || (direction == Direction::Horizontal && ((column + str_len) > ROW_LENGTH))) {
            throw out_of_range("Invalid input! Row index out of bounds!");
        }
    }

    void Notebook::validateIntegers(std::initializer_list<int> numbers) {
        for (const int &num: numbers) {
            if (num < 0) {
                throw out_of_range("Invalid input! Received negative integer!");
            }
        }
    }

    void Notebook::checkPrintable(const string &str) {
        for (char c: str) {
            if (isprint(c) == 0) {
                throw invalid_argument("Invalid input! String is not printable!");
            }
            if (c == TILDA) {
                throw invalid_argument("Invalid input! Tilda is an invalid character!");
            }
            if (c != ' ') {
                if (isspace(c) != 0) {
                    throw invalid_argument("Invalid input! Contains newline or carriage return!");
                }
            }
        }
    }
}