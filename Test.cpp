#include <random>
#include "doctest.h"
#include "sources/Notebook.hpp"

using ariel::Notebook;
using ariel::Direction;
using std::string;
using std::random_device;

/**
 * @return randomly generated character
 */
char getRandomChar() {
    random_device rd;
    return (char) ('a' + rd() % 26); // rd() generates a random value
}

/**
 * @param length
 * @return randomly generated string of the given length
 */
string stringGenerator(int length) {
    int iteration = 0;
    string res;
    while (iteration < length) {
        res += getRandomChar(); // use helper function
        iteration++;
    }
    return res;
}

/*
 * doctest SUBCASE:
 * "One leaf subcase is executed on each run through a TEST_CASE(). The other subcases are skipped. Next time the next
 * subcase is executed and so on until no new subcases are encountered."
 * From documentation: https://tinyurl.com/2p9eb5mb
 */

TEST_CASE ("Good Input") {
    Notebook notebook;

    string input1 = "Hello World!";
    notebook.write(0, 0, 0, Direction::Horizontal, input1);
            CHECK(notebook.read(0, 0, 0, Direction::Horizontal, input1.size()) == input1);

    string input2 = "12345";
    string output2 = "12~45";
    notebook.write(0, 1, 1, Direction::Vertical, input2);
            CHECK(notebook.read(0, 1, 1, Direction::Horizontal, input2.size()) == input2);
    notebook.erase(0, 3, 1, Direction::Vertical, 1);
            CHECK(notebook.read(0, 1, 1, Direction::Horizontal, input2.size()) == output2);

    string input3 = "a";
    string output3 = "_a";
    notebook.write(99, 99, 99, Direction::Horizontal, input3);
            CHECK(notebook.read(99, 99, 99, Direction::Horizontal, input3.size()) == input3);
            CHECK(notebook.read(99, 99, 98, Direction::Horizontal, output3.size()) == output3);

}

TEST_CASE ("Invalid Strings") {
    Notebook notebook;

            SUBCASE("Tilda") { // program uses this character to mark deleted text
                CHECK_THROWS(notebook.write(0, 0, 0, Direction::Horizontal, "~"));
                CHECK_THROWS(notebook.write(0, 1, 0, Direction::Horizontal, "~~~~~~"));
                CHECK_THROWS(notebook.write(0, 2, 1, Direction::Vertical, "~~a~bc~~~"));
    }

            SUBCASE("Null Terminator") {
                CHECK_THROWS(notebook.write(1, 0, 0, Direction::Horizontal, "\0"));
                CHECK_THROWS(notebook.write(1, 1, 0, Direction::Horizontal, "\0abc"));
    }

            SUBCASE("Newline, carriage return") {
                CHECK_THROWS(notebook.write(2, 0, 0, Direction::Horizontal, "\n"));
                CHECK_THROWS(notebook.write(2, 0, 1, Direction::Horizontal, "hi\nhello"));
                CHECK_THROWS(notebook.write(2, 1, 0, Direction::Horizontal, "~~~\r~"));
                CHECK_THROWS(notebook.write(2, 2, 0, Direction::Vertical, "yes\rno"));
                CHECK_THROWS(notebook.write(2, 3, 0, Direction::Vertical, "\r"));
                CHECK_THROWS(notebook.write(3, 1, 1, Direction::Vertical, "_\n__~___~"));
    }

}

TEST_CASE ("Write Method") {
    Notebook notebook;

            SUBCASE("Out of bounds") {
        string over_100 = stringGenerator(105);
                CHECK_THROWS(notebook.write(0, 0, 95, Direction::Horizontal, "abcdefg"));
                CHECK_THROWS(notebook.write(0, 99, 0, Direction::Vertical, "!@#$%^&*()-+=[]|"));
                CHECK_THROWS(notebook.write(1, 0, 0, Direction::Horizontal, over_100));
                CHECK_THROWS(notebook.write(1, 1, 0, Direction::Vertical, over_100));
    }

            SUBCASE("Write over existing text") {
        notebook.write(0, 0, 0, Direction::Horizontal, "acdat");
                CHECK_THROWS(notebook.write(0, 0, 0, Direction::Horizontal, "___"));
        notebook.write(1, 0, 0, Direction::Vertical, "set");
                CHECK_THROWS(notebook.write(1, 1, 0, Direction::Vertical, "~+"));
    }

            SUBCASE("Write over deleted text") {
        notebook.write(5, 0, 0, Direction::Horizontal, "a");
        notebook.write(5, 1, 1, Direction::Vertical, "text");
        notebook.erase(5, 0, 0, Direction::Horizontal, 1);
        notebook.erase(5, 1, 1, Direction::Vertical, 4);

                CHECK_THROWS(notebook.write(5, 0, 0, Direction::Horizontal, "b"));
                CHECK_THROWS( // same string as the one that was erased
                notebook.write(5, 1, 1, Direction::Vertical, "text"));
    }

}

TEST_CASE ("Negative Input") {
    Notebook notebook;

            SUBCASE("Read Method") {
                CHECK_THROWS(notebook.read(-1000, 0, 5, Direction::Horizontal, -20));
                CHECK_THROWS(notebook.read(2, -24, -8, Direction::Vertical, 0));
    }

            SUBCASE("Write Method") {
                CHECK_THROWS(notebook.write(-23, 5, 5, Direction::Horizontal, "xxx"));
                CHECK_THROWS(notebook.write(-6, -45, -30, Direction::Vertical, "yyy"));
    }

            SUBCASE("Erase Method") {
                CHECK_THROWS(notebook.erase(-23, 5, 5, Direction::Horizontal, 3));
                CHECK_THROWS(notebook.erase(-6, -45, -30, Direction::Vertical, -55));
    }

            SUBCASE("Show Method") {
                CHECK_THROWS(notebook.show(-30));
                CHECK_THROWS(notebook.show(-23));
                CHECK_NOTHROW(notebook.show(0));
    }

}
