#include "sudoku.h"

char sudoku[9][9];
char numbers[9] = {'1','2','3','4','5','6','7','8','9'};
int gDifficultyLevel;

static void generateZeroThRow(char *firstRow);
static int generateRandomIndex(void);

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
 *   1. Fill all the diagonal 3x3 matrices. [subunit 1,5,9,3,7]
 *   2. Fill recursively rest of the non-diagonal matrices. [subunit 4,6]
 *      For every cell to be filled, we try all numbers until
 *      we find a safe number to be placed.  
 *   3. Once matrix is fully filled, remove K elements
 *      randomly to complete game
*/


void sudoku_generateSudoku(void)
{   
    // yet to implement
}


void sudoku_displayGeneratedSudoku(void)
{   
    printf("\n\n");

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%c ", sudoku[i][j]);
        }
        printf("\n");
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

    for (int i = subunitRow; i < (subunitRow + 3); i++){
        for (int j = subunitCol; j < (subunitCol + 3); j++){
            if (numbers[index] == sudoku[i][j])   
                return 1;
        }
    }
    return 0;
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

// TODO : 1. implement sudoku_generateSudoku function by maintaining the algorithm
//        2. mask some positions of sudoku acc to difficulty level
//        3. print final sudoku in a nice design 