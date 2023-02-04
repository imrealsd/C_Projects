#include "sudoku.h"

int gDifficultyLevel;

void sudoku_printWelcomeMessege(void)
{
    printf("-----------------------------\n");
    printf("|    *                *     |\n");
    printf("|   *|*              *|*    |\n");
    printf("|  **|**  GENERATE  **|**   |\n");
    printf("| ***|***  SUDOKU  ***|***  |\n");
    printf("|   _|_              _|_    |\n");
    printf("-----------------------------\n");
}

void sudoku_getDifficultyLevel(void)
{
    printf("|---------------------------|\n");
    printf("|1.Easy | 2.Medium | 3.Hard |\n");
    printf("|---------------------------|\n");
    printf("Choose Level [1/2/3]: ");
}