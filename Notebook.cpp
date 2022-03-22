#include "Notebook.hpp"

using std::string;

typedef unsigned int uint;

namespace ariel {

    Notebook::Notebook() {
//        this->notes = new map<int, map<int, vector<char>>>;
    }

    Notebook::~Notebook() {

    }

    void Notebook::write(uint page, uint row, uint column, Direction direction, const string &str) {
        std::cout << str << '\n';
    }

    string Notebook::read(uint page, uint row, uint column, Direction direction, uint len) { return ""; }

    void Notebook::erase(uint page, uint row, uint column, Direction direction, uint len) {}

    void Notebook::show(uint page) {}

}