#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

#include <iostream>
#include <string>
#include <array>
#include <unordered_map>
#include <map>
#include "Direction.hpp"

namespace ariel {

    class Notebook {

    private:
        std::unordered_map<int, std::map<int, std::array<char, 100>>> _notebook;

    public:

        void write(int page, int row, int column, Direction direction, const std::string &str);

        std::string read(int page, int row, int column, Direction direction, int str_len);

        void erase(int page, int row, int column, Direction direction, int str_len);

        void show(int page);

    };

}

#endif //CPP_EX2_NOTEBOOK_HPP
