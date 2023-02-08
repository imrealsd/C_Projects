#include "sudoku.h"

char sudoku[9][9];
char numbers[9] = {'1','2','3','4','5','6','7','8','9'};
int gDifficultyLevel;


static int generateRandomIndex(void);
static void generateIndependentSubunit_1_5_9(void);
static int is_existingInSubunit(int row, int col, int index);
static int is_existingInColumn(int col, int index);
static int is_existingInRow(int row, int index);


void sudoku_printWelcomeMessege(void)
{   
    printf("_____________________________\n");
    printf("|    __________________     |\n");
    printf("|    |                |     |\n");  
    printf("|    |     SUDOKU     |     |\n");
    printf("|    |    GENERATOR   |     |\n");
    printf("|    |________________|     |\n");
    printf("|___________________________|\n");

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
 *   1    x 1 x | x 2 x | x 3 x    
 *   2    x x x | x x x | x x x        
 *        ---------------------
 *   3    x x x | x x x | x x x
 *   4    x 4 x | x 5 x | x 6 x  
 *   5    x x x | x x x | x x x
 *        ---------------------
 *   6    x x x | x x x | x x x
 *   7    x 7 x | x 8 x | x 9 x
 *   8    x x x | x x x | x x x
 *  [row]
 * ------------------------------
*/

/**
 * Genertion Algorithm:
 * 
 *   1. Fill all the diagonal 3x3 matrices. [subunit 1,5,9]
 *   2. Fill recursively rest of the non-diagonal matrices. [subunit 4,6,3,7]
 *      For every cell to be filled, we try all numbers until
 *      we find a safe number to be placed.  
 *   3. Once matrix is fully filled, remove K elements
 *      randomly to complete game
*/


void sudoku_generateSudoku(void)
{   
    memset(sudoku, '0', sizeof(sudoku));
    generateIndependentSubunit_1_5_9();
}


void sudoku_displayGeneratedSudoku(void)
{   
    printf("\n\n");

    for (int i = 0; i < SUDOKU_ROW_SIZE; i++){
        printf("-------------------------------------\n");
        for (int j = 0; j < SUDOKU_COL_SIZE; j++){
            printf("| %c ", sudoku[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------------------\n");
}


static int is_existingInRow(int row, int index)
{
    for (int i = 0; i < SUDOKU_ROW_SIZE; i++){
        if (sudoku[row][i] == numbers[index]){
            return 1;
        }
    }
    return 0;
}


static int is_existingInColumn(int col, int index)
{
    for (int i = 0; i < SUDOKU_COL_SIZE; i++){
        if (sudoku[i][col] == numbers[index]){
            return 1;
        }
    }
    return 0;
}


static int is_existingInSubunit(int row, int col, int index)
{   
    int subunitRow;
    int subunitCol;
    
    if ((row <= 2 && row >= 0)){
        subunitRow = 0;
    } else if (row <= 5 && row >= 3){
        subunitRow = 3;
    } else if (row <= 8 && row >= 6){
        subunitRow = 6;
    }

    if (col <= 2 && col >= 0){
        subunitCol = 0;
    } else if (col <= 5 && col >= 3){
        subunitCol = 3;
    } else if (col <= 8 && col >= 6){
        subunitCol = 6;
    }

    for (int i = subunitRow; i < (subunitRow + SUDOKU_SUBUNIT_ROW_SIZE); i++){
        for (int j = subunitCol; j < (subunitCol + SUDOKU_SUBUNIT_COL_SIZE); j++){
            if (numbers[index] == sudoku[i][j])   
                return 1;
        }
    }
    return 0;
} 


static int generateRandomIndex(void)
{
    int index = (rand() % SUDOKU_TOTAL_DIFFERENT_NUM);
    return index;
}


static void generateIndependentSubunit_1_5_9(void)
{   
    int subunitRow   = 0;
    int subunitCol   = 0;
    int subunitCount = 0;
    int successFlag  = 0;
    int index;


    while (subunitCount < 3){

        if (subunitCount == 0){
            subunitRow = 0;
            subunitCol = 0;
        } else if (subunitCount == 1){
            subunitRow = 3;
            subunitCol = 3;
        } else if (subunitCount == 2){
            subunitRow = 6;
            subunitCol = 6;
        }


        for (int i = subunitRow; i < (subunitRow + SUDOKU_SUBUNIT_ROW_SIZE); i++){
            for (int j = subunitCol; j < (subunitCol + SUDOKU_SUBUNIT_COL_SIZE); j++){
                while (successFlag != 1){
                    index = generateRandomIndex();
                    if ((!is_existingInSubunit(subunitRow,subunitRow,index))){
                        sudoku[i][j] = numbers[index];
                        successFlag = 1;
                    }
                }
                successFlag = 0;
            }
        }
        subunitCount++;
    } 
}


// TODO : 1. implement generateRestOfsudoku func
//        2. mask some positions of sudoku acc to difficulty level
//        3. print final sudoku in a nice design 