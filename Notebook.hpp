#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

#include <iostream>
#include <string>
//#include <vector>
//#include <utility>
//#include <unordered_map>
#include "Direction.hpp"

namespace ariel {

    class Notebook {
    private:
//        std::unordered_map<std::pair<int, int>, std::vector<char>> notebook;
//        map<int, map<int, vector < char>>> *notes;
//        map <pair<int, int>, vector<char>> notes;
    public:
        Notebook();

        ~Notebook();

        void write(unsigned int, unsigned int, unsigned int, Direction, const std::string &);

        std::string read(unsigned int, unsigned int, unsigned int, Direction, unsigned int);

        void erase(unsigned int, unsigned int, unsigned int, Direction, unsigned int);

        void show(unsigned int);

    };

}

#endif //CPP_EX2_NOTEBOOK_HPP
