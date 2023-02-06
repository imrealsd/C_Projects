#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef SUDOKU_H 
#define SUDOKU_H

#define SUDOKU_TOTAL_DIFFERENT_NUM 9
#define SUDOKU_ROW_SIZE  9
#define SUDOKU_COL_SIZE  9
#define SUDOKU_SUBUNIT_ROW_SIZE 3
#define SUDOKU_SUBUNIT_COL_SIZE 3

void sudoku_printWelcomeMessege(void);
void sudoku_getDifficultyLevel(void);
void sudoku_generateSudoku(void);
void sudoku_displayGeneratedSudoku(void);

#endif //  SUDOKU_H 