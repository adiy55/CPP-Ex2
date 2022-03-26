#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

#include <iostream>
#include <cctype>
#include <string>
#include <unordered_map>
#include "Direction.hpp"
#include "Page.hpp"

namespace ariel {

    class Notebook { // todo: const methods?

    private:

        std::unordered_map<int, Page> _notebook;

        Page &getPage(int page_number);

        static void validateIntegers(int, int, int, Direction, int = 0);

        static void checkNonNegative(std::initializer_list<int> numbers);

        static void checkWritable(const std::string &str);

    public:

        void write(int page_number, int row, int column, Direction direction, const std::string &str);

        std::string read(int page_number, int row, int column, Direction direction, int str_len);

        void erase(int page_number, int row, int column, Direction direction, int str_len);

        void show(int page_number);

    };

}

#endif //CPP_EX2_NOTEBOOK_HPP
