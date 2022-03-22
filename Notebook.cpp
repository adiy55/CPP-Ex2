#include "Notebook.hpp"

using std::cout;
using std::string;
using std::unordered_map;
using std::map;

typedef unsigned int uint;

namespace ariel {

    void Notebook::write(uint page, uint row, uint column, Direction direction, const string &str) {
        m_notebook.find(page);
    }

    string Notebook::read(uint page, uint row, uint column, Direction direction, uint len) {
        m_notebook.find(page);
        return "";
    }

    void Notebook::erase(uint page, uint row, uint column, Direction direction, uint len) {}

    void Notebook::show(uint page) {
        m_notebook[100][0] = {'a'};
        if (m_notebook.contains(page)) { // todo: from 20++?
            map curr_page = m_notebook.at(page);
            for(auto &[a, b] : curr_page){
                for (char i : b) {
                    cout << i;
                }
                cout << '\n';
            }
        }

    }

}