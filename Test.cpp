#include "doctest.h"
#include "Notebook.hpp"

using namespace ariel;
using ariel::Notebook;
using ariel::Direction;
using std::string;

TEST_CASE ("Good Input") {
    Notebook notebook;
    string input1 = "Hello World";
    notebook.write(0, 0, 0, Direction::Horizontal, input1);
            CHECK(input1 == notebook.read(0, 0, 0, Direction::Horizontal, input1.size()));

    string input2 = "12345";
    notebook.write(0, 1, 1, Direction::Vertical, input2);
            CHECK(input2 == notebook.read(0, 1, 1, Direction::Horizontal, input2.size()));

    string input3 = "a";
    notebook.write(99, 99, 99, Direction::Horizontal, input3);
            CHECK(input3 == notebook.read(99, 99, 99, Direction::Horizontal, input3.size()));

}

TEST_CASE ("Invalid Strings") {
    Notebook notebook;

            SUBCASE("Tilda") {
                CHECK_THROWS(notebook.write(0, 0, 0, Direction::Horizontal, "~"));
                CHECK_THROWS(notebook.write(0, 1, 0, Direction::Horizontal, "~~~~~~"));
                CHECK_THROWS(notebook.write(0, 2, 1, Direction::Vertical, "~~~~~~"));
    }

            SUBCASE("Null Terminator") {
                CHECK_THROWS(notebook.write(1, 0, 0, Direction::Horizontal, "\0"));
                CHECK_THROWS(notebook.write(1, 1, 0, Direction::Horizontal, "\0abc"));
    }

            SUBCASE("New line, carriage return") {
                CHECK_THROWS(notebook.write(2, 0, 0, Direction::Horizontal, "\n"));
                CHECK_THROWS(notebook.write(2, 0, 0, Direction::Horizontal, "hi\nhello"));
                CHECK_THROWS(notebook.write(2, 1, 0, Direction::Horizontal, "~~~\r~"));
                CHECK_THROWS(notebook.write(2, 2, 0, Direction::Vertical, "yes\rno"));
    }

            SUBCASE("Underscore") {
                CHECK_THROWS(notebook.write(2, 0, 0, Direction::Horizontal, "____"));
                CHECK_THROWS(notebook.write(2, 0, 0, Direction::Vertical, "_"));
                CHECK_THROWS(notebook.write(2, 1, 0, Direction::Vertical, "_\n__~___~"));
    }

}

TEST_CASE ("Write Method") {
    Notebook notebook;
    notebook.write(5, 0, 0, Direction::Horizontal, "a");
    notebook.write(5, 1, 1, Direction::Vertical, "text");
    notebook.erase(5, 0, 0, Direction::Horizontal, 1);
    notebook.erase(5, 1, 1, Direction::Vertical, 4);

    string over_100;
    char start = '0';
    for (int i = 0; i < 105; ++i) {
        over_100 += start;
        start++;
    }

            SUBCASE("Out of bounds") {
                CHECK_THROWS(notebook.write(0, 95, 0, Direction::Horizontal, "abcdefg"));
                CHECK_THROWS(notebook.write(0, 0, 99, Direction::Vertical, "!@#$%^&*()-+=[]|"));
                CHECK_THROWS(notebook.write(1, 0, 0, Direction::Horizontal, over_100));
                CHECK_THROWS(notebook.write(1, 0, 99, Direction::Vertical, over_100));
    }

            SUBCASE("Writing over deleted text") {
                CHECK_THROWS(notebook.write(5, 0, 0, Direction::Horizontal, "b"));
                CHECK_THROWS(notebook.write(5, 1, 1, Direction::Vertical, "text")); // same string as before erased

    }

}
