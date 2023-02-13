/*Public includes*/
#include <stdio.h>

/*Private includes*/
#include "sudoku.h"

/**
 * @brief program entry point 
 */
int main(int argc, char *argv[])
{   
    sudoku_printWelcomeMessege();
    sudoku_getDifficultyLevel();
    sudoku_generateSudoku();
    sudoku_displayGeneratedSudoku();
    return 0;
}