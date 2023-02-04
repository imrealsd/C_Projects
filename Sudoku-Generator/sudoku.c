#include "sudoku.h"

char sudoku[9][9];
char numbers[9] = {'1','2','3','4','5','6','7','8','9'};
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
    scanf("%d", &gDifficultyLevel);
}


/**
 * Sudoku Structure [divided into 9 sub-units]:
 * Total Numbers : 9 x 9 = 81
 * Each subunit has 9 digits [1-9] [no duplicates]
 * Each row has 9 digits     [1-9] [no duplicates]
 * Each column has 9 digits  [1-9] [no duplicates]
 * 
 * ----------------------------
 *        0 1 2   3 4 5   6 7 8  [col]
 * 
 *   0    x x x | x x x | x x x     
 *   1    x x x | x x x | x x x    
 *   2    x x x | x x x | x x x        
 *        ---------------------
 *   3    x x x | x x x | x x x
 *   4    x x x | x x x | x x x  6
 *   5    x x x | x x x | x x x
 *        ---------------------
 *   6    x x x | x x x | x x x
 *   7    x x x | x x x | x x x
 *   8    x x x | x x x | x x x
 *  [row]
 * ------------------------------
*/

/**
 * Genertion Algorithm:
 * initialize all emenets of sudoku to zero
 * generate 9 unique numbers for 0th row
 * generate 1 numbers for 1st row 0th col 
 * check row, col & subunit for duplicates [if duplicate -> generate again]
 * continue for  8 rows x 9 cols
*/


void sudoku_generateSudoku(void)
{   
    int index;

    memset(sudoku, 0, sizeof(sudoku));
    generateZeroThRow(sudoku[0]);

    for (int row = 1; row < 9; row ++){
        for (int col = 0; col < 9; col++){

            TRY_AGAIN:
            int index = generateRandomIndex();
            if ((! is_existingInRow(row, index)) && (! is_existingInColumn(col, index)) 
                                         && (! is_existingInSubunit(row, col, index))){

                sudoku[row][col] = numbers[index];
            } else {
                goto TRY_AGAIN;
            }
        }
    }
}


static int is_existingInRow(int row, int index)
{
    for (int i = 0; i < 9; i++){
        if (sudoku[row][i] == numbers[index]){
            return 1;
        }
    }
    return 0;
}


static int is_existingInColumn(int col, int index)
{
    for (int i = 0; i < 9; i++){
        if (sudoku[i][col] == numbers[index]){
            return 1;
        }
    }
    return 0;
}


static int is_existingInSubunit(int row, int col, int index)
{   
    // yet to implement
}


static int generateRandomIndex(void)
{
    srand((unsigned int) time(NULL));
    int index = (rand() % 9);
    return index;
}


static void generateZeroThRow(char *firstRow)
{   
    srand((unsigned int) time(NULL));
    memset(firstRow, 0, 9);
    int count = 0;
    int matchFlag = 0;

    while (count <= 8){
        GENERATE_AGAIN:
        int index = (rand() % 9);
        for (int i = 0; i < 9; i++){
            if (firstRow[i] == numbers[index]){
                matchFlag = 1;
                break;
            }
        }
        if (matchFlag == 1){
            matchFlag = 0;
            goto GENERATE_AGAIN;
        } else {
            firstRow[count] = numbers[index];
            count++;
        }
    }
}

// TODO : 1. implement is_existingInSubunit function
//        2. mask some positions of sudoku acc to difficulty level
//        3. print final sudoku in a nice design 