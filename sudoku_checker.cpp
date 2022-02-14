#include <iostream>
#include <fstream>
#include <set>

class Sudoku {
private:
    int puzzle[9][9]{};

    bool isRowValid(int row) {
        std::set<int> s;

        for (int c = 0; c < 9; c++) { // Col
            if (puzzle[row][c] != 0) {
                if (!s.insert(puzzle[row][c]).second) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isColValid(int col) {
        std::set<int> s;

        for (auto &r: puzzle) { // Row
            if (r[col] != 0) {
                if (!s.insert(r[col]).second) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isSquareValid(int row, int col) {
        std::set<int> s;

        for (int r = row; r < (row + 3); r++) {  // Row
            for (int c = col; c < (col + 3); c++) { // Col
                if (!s.insert(puzzle[r][c]).second) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    explicit Sudoku(const std::string &fname) {
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

    void print() {
        for (auto &r: puzzle) {
            for (int c: r) {
                std::cout << c << ' ';
            }
            std::cout << std::endl;
        }
    }

    void check() {
        // Check rows
        for (int r = 0; r < 9; r++) {
            if (isRowValid(r) == 0) {
                std::cout << "Wrong solution!" << std::endl;
                return;
            }
        }

        // Check cols
        for (int c = 0; c < 9; c++) {
            if (isColValid(c) == 0) {
                std::cout << "Wrong solution!" << std::endl;
                return;
            }
        }
        int invalidSquare;

        for (int r = 0; r < 9; r+=3) {
            for (int c = 0; c < 9; c+=3) {
                invalidSquare = !isSquareValid(r, c);

                if (invalidSquare) {
                    std::cout << "Wrong solution!" << std::endl;
                    return;
                }
            }
        }
        std::cout << "Solution is good!" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::string fname = std::string(argv[1]);

    Sudoku puzzle(fname);

    puzzle.print();

    puzzle.check();
}
