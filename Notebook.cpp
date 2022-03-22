#include "Notebook.hpp"

using std::string;

namespace ariel {

    void Notebook::write(int page, int row, int column, Direction direction, const string &str) {
        _notebook.find(page);
    }

    string Notebook::read(int page, int row, int column, Direction direction, int str_len) {
        _notebook.find(page);
        return "";
    }

    void Notebook::erase(int page, int row, int column, Direction direction, int str_len) {}

    void Notebook::show(int page) {
        _notebook.find(page);
    }

}