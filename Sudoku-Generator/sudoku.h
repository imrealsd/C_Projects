/*Public includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Define driver*/
#ifndef SUDOKU_H 
#define SUDOKU_H

/*Value Defines */
#define SUDOKU_TOTAL_DIFFERENT_NUM 9
#define SUDOKU_ROW_SIZE  9
#define SUDOKU_COL_SIZE  9
#define SUDOKU_SUBUNIT_ROW_SIZE 3
#define SUDOKU_SUBUNIT_COL_SIZE 3

/*Function prototypes*/

/**
 * @brief print welcome msg on screen
 * @param none
 * @retval none
 */
void sudoku_printWelcomeMessege(void);

/**
 * @brief get sudoku difficulty level form user
 * @param none
 * @retval none
 */
void sudoku_getDifficultyLevel(void);

/**
 * @brief generate sudoku
 * @param none
 * @retval none
 */
void sudoku_generateSudoku(void);

/**
 * @brief print generated sudoku on screen
 * @param none
 * @retval none
 */
void sudoku_displayGeneratedSudoku(void);

#endif //  SUDOKU_H 