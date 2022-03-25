#include "Notebook.hpp"

using std::string;
using std::isprint;
using std::invalid_argument;

namespace ariel {

    void Notebook::write(int page_number, int row, int column, Direction direction, const string &str) {
        Page &page = this->getPage(page_number);
        page.write(row, column, direction, str);
    }

    string Notebook::read(int page_number, int row, int column, Direction direction, int str_len) {
        Page &page = this->getPage(page_number);
        return page.getSection(row, column, direction, str_len);
    }

    void Notebook::erase(int page_number, int row, int column, Direction direction, int str_len) {
        Page &page = this->getPage(page_number);
        page.erase(row, column, direction, str_len);
    }

    void Notebook::show(int page_number) {
        Page &page = this->getPage(page_number);
        page.printPage();
    }

    Page &Notebook::getPage(int page) {
        if (!_notebook.contains(page)) {
            _notebook[page] = Page();
        }
        return _notebook[page];
    }
}