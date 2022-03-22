#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Direction.hpp"

namespace ariel {

    class Notebook {
        std::unordered_map<unsigned int, std::unordered_map<unsigned int, std::vector<char>>> m_notebook;

    public:

        void write(unsigned int, unsigned int, unsigned int, Direction, const std::string &);

        std::string read(unsigned int, unsigned int, unsigned int, Direction, unsigned int);

        void erase(unsigned int, unsigned int, unsigned int, Direction, unsigned int);

        void show(unsigned int);

    };

}

#endif //CPP_EX2_NOTEBOOK_HPP
