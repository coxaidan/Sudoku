#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <string>

Sudoku::Sudoku(std::string fname) {
    std::ifstream infile;
    infile.open(fname);

    if (infile.fail()) {
        std::cerr << "Can't open " << fname << '\n';
        return;
    }

    for (auto &r: puzzle) {
        for (int &c: r) {
            infile >> c;
        }
    }
    infile.close();
}


bool Sudoku::solve() {
    int row, col;

    if (!checkEmpty(row, col)) {
        return true;
    }

    // Let's try filling this cell with possible numbers 1-9
    for (int num = 1; num <= 9; num++) {
        if (checkAll(row, col, num)) {

            // At this point - it seems like this number could work
            puzzle[row][col] = num;

            // Let's return success on this particular number
            if (solve()) {
                return true;
            }

            // At this point the current number did not work - set it back to 0
            puzzle[row][col] = 0;
        }
    }
    return false;
}

bool Sudoku::checkEmpty(int &row, int &col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (puzzle[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::checkAll(int row, int col, int num) {
    return !checkRow(row, num) && !checkCol(col, num) && !checkSquare(row, col, num);
}

bool Sudoku::checkRow(int row, int num) {
    for (int c = 0; c < 9; c++) {
        if (puzzle[row][c] == num) {
            return true;
        }
    }
    return false;
}

bool Sudoku::checkCol(int col, int num) {
    for (auto &r: puzzle) {
        if (r[col] == num) {
            return true;
        }
    }
    return false;
}

bool Sudoku::checkSquare(int row, int col, int num) {
    row = row - row % 3;
    col = col - col % 3;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (puzzle[r + row][c + col] == num) {
                // The number is already in the col!
                return true;
            }
        }
    }
    return false;
}

// this function prints your puzzle in 2D format with commas separating your values
void Sudoku::print() {
    for (auto &r: puzzle) {
        for (int c: r) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
}