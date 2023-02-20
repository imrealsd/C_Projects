#include "snake.h"




char gSpace = ' ' ;
char gsnakeSymbol = 'o';
char gFoodSymbol = '*';

void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead );



void snake_gameInit(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    memset(gameScreen, gSpace, (SCREEN_ROW * SCREEN_COL));
    /*Initialize seed of random number generator*/
    srand((unsigned long) time(NULL));
    add_initialSnake(gameScreen, pHead);
}


void snake_generateFoodPosition(int* const row, int* const col)
{
    int randNum;

    randNum = rand() % SCREEN_ROW ;
    *row = randNum;
    randNum = rand() % SCREEN_COL ;
    *col = randNum;
}


bool snake_isEatingFood(int foodRow, int foodColumn, snakeUnit* pHead)
{
    if (pHead->row == foodRow && pHead == foodColumn){
        return True;
    }
    return Flase;
}


void snake_increaseSnake(snakeUnit* pHead, int foodRow, int foodColumn)
{   
    snakeUnit *newUnit = (snakeUnit *)malloc(sizeof(snakeUnit));

    newUnit->row = foodRow;
    newUnit->column = foodColumn;
    newUnit->next = pHead;
    pHead = newUnit;
}


void snake_clearGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    system("clear");
    memset(gameScreen,gSpace, (SCREEN_ROW * SCREEN_COL));
}


void snake_waitGameScreen(int time)
{
    for (volatile long int i = 0; i < (time * 1000); i++);
}


void snake_addFoodToGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL], const int row, const int col)
{   
    gameScreen[row][col] = gFoodSymbol; 
}


void snake_displayGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL])
{
    int row = 0;
    int col = 0;

    for (row = 0; row < SCREEN_ROW; row++){
        for (col = 0; col < SCREEN_COL; col++){
            printf("%c", gameScreen[row][col]);
        }
        printf("\n");
    }
}


void snake_updateSnakePosition(char userInput, char gameScreen [SCREEN_ROW][SCREEN_COL])
{
    if (userInput == 'w'){

    } else if (userInput == 's'){

    } else if (userInput == 'a'){

    } else if (userInput == 'd'){

    }
}

/****** Static Functions ********/

void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    snakeUnit *temp = (snakeUnit *)malloc(sizeof(snakeUnit));

    temp->next = NULL;
    temp->row = 0;
    temp->column = 0;
    pHead = temp;

    gameScreen[pHead->row][pHead->column] = gsnakeSymbol;
}

