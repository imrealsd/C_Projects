#include <stdio.h>
#include "sudoku.h"

int main(int argc, char *argv[])
{   
    sudoku_printWelcomeMessege();
    sudoku_getDifficultyLevel();
    sudoku_generateSudoku();
    sudoku_displayGeneratedSudoku();
    return 0;
}