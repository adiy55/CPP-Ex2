#include "Notebook.hpp"

using std::string;

typedef unsigned int uint;

namespace ariel {

    void Notebook::write(uint page, uint row, uint column, Direction direction, const string &str) {
        _notebook.find(page);
    }

    string Notebook::read(uint page, uint row, uint column, Direction direction, uint str_len) {
        _notebook.find(page);
        return "";
    }

    void Notebook::erase(uint page, uint row, uint column, Direction direction, uint str_len) {}

    void Notebook::show(uint page) {
        _notebook.find(page);
    }

}