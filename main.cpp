#include <iostream>
#include "sudoku.h"

int main(int argc, char *argv[]) {
    std::string fname = std::string(argv[1]);

    Sudoku mySudoku(fname);

    if (mySudoku.solve()) {
        mySudoku.print();
    } else {
        std::cout << "No Solution!" << std::endl;
    }

    return 0;
}
