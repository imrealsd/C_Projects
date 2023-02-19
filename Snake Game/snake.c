#include "snake.h"




void snake_gameInit(char** gameScreen)
{   
    memset(gameScreen, 0, sizeof(gameScreen));
    /*Initialize seed of random number generator*/
    srand((unsigned long) time(NULL));
}


void snake_generateFoodPosition(int* const row, int* const col)
{
    int randNum;

    randNum = rand() % SCREEN_ROW ;
    *row = randNum;
    randNum = rand() % SCREEN_COL ;
    *col = randNum;
}


void snake_clearScreen(char** gameScreen)
{
    system("clear");
    memset(gameScreen, 0, sizeof(gameScreen));
}


void snake_addFoodToScreen(char** gameScreen, const int row, const int col)
{   
    char foodSymbol = '*';
    gameScreen[row][col] = foodSymbol; 
}