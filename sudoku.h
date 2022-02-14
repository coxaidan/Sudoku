#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <iostream>

class Sudoku {
    private:
        int puzzle[9][9]{};

        bool checkAll(int row, int col, int num);

        bool checkRow(int row, int num);
        bool checkCol(int col, int num);
        bool checkSquare(int row, int col, int num);

        bool checkEmpty(int &row, int &col);

    public:
        explicit Sudoku(std::string fname);

        bool solve();

        void print();
};

#endif
