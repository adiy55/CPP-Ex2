#include "Notebook.hpp"
#include "Constants.hpp"

using std::string;
using std::isprint;
using std::isspace;
using std::invalid_argument;
using std::out_of_range;
using namespace constants;

namespace ariel {

    /**
     * Write on a specific part of a page.
     * @param str text to write
     */
    void Notebook::write(int page_number, int row, int column, Direction direction, const string &str) {
        validateIntegers(page_number, row, column, direction);
        checkWritable(str);
        Page &page = this->getPage(page_number);
        page.write(row, column, direction, str);
    }

    /**
     * @return specified part of the text on a page
     */
    string Notebook::read(int page_number, int row, int column, Direction direction, int str_len) {
        validateIntegers(page_number, row, column, direction, str_len);
        Page &page = this->getPage(page_number);
        return page.getSection(row, column, direction, str_len);
    }

    /**
     * Marks over a specific part of a page.
     */
    void Notebook::erase(int page_number, int row, int column, Direction direction, int str_len) {
        validateIntegers(page_number, row, column, direction, str_len);
        Page &page = this->getPage(page_number);
        page.erase(row, column, direction, str_len);
    }

    /**
     * Prints all page contents.
     */
    void Notebook::show(int page_number) {
        checkNonNegative({page_number});
        Page &page = this->getPage(page_number);
        page.printPage();
    }

    /**
     * If page does not exists- initializes one.
     * @return reference to the page
     */
    Page &Notebook::getPage(int page_number) {
        if (_notebook.count(page_number) == 0) {
            _notebook[page_number] = Page();
        }
        return _notebook[page_number];
    }

    /**
     * Throws exception if numbers are negative or out of bounds.
     * str_len default value is 0 to provide compatibility with write function (see in header file).
     */
    void Notebook::validateIntegers(int page_number, int row, int column, Direction direction, int str_len) {
        checkNonNegative({page_number, row, column, str_len}); // call helper function
        if ((column >= ROW_LENGTH) || (direction == Direction::Horizontal && ((column + str_len) > ROW_LENGTH))) {
            throw out_of_range("Invalid input! Row index out of bounds!");
        }
    }

    /**
     * Throws exception if numbers are negative.
     */
    /*
     * "initializer_list<T> is a lightweight proxy object that provides access to an array of objects of type const T."
     * Constructed with curly brackets {}.
     * Used in this case to pass an unknown amount of integers in an iterable container.
     * Additional information: https://en.cppreference.com/w/cpp/utility/initializer_list
     */
    void Notebook::checkNonNegative(std::initializer_list<int> numbers) {
        for (const int &num: numbers) {
            if (num < 0) {
                throw out_of_range("Invalid input! Received negative integer!");
            }
        }
    }

    /**
     * Checks if a given string is valid to write.
     */
    void Notebook::checkWritable(const string &str) {
        for (char c: str) {
            if (isprint(c) == 0) {
                throw invalid_argument("Invalid input! String is not printable!");
            }
            if (c == TILDA) {
                throw invalid_argument("Invalid input! Tilda is an invalid character!");
            }
            if (c != ' ' && isspace(c) != 0) {
                throw invalid_argument("Invalid input! Contains newline or carriage return!");
            }
        }
    }
}