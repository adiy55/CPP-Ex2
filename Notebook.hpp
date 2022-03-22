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
        std::unordered_map<unsigned int, std::map<unsigned int, std::array<char, 100>>> _notebook;

    public:

        void
        write(unsigned int page, unsigned int row, unsigned int column, Direction direction, const std::string &str);

        std::string
        read(unsigned int page, unsigned int row, unsigned int column, Direction direction, unsigned int str_len);

        void erase(unsigned int page, unsigned int row, unsigned int column, Direction direction, unsigned int str_len);

        void show(unsigned int page);

    };

}

#endif //CPP_EX2_NOTEBOOK_HPP
