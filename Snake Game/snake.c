#include "snake.h"

char gSpace = ' ' ;
char gSnakeSymbol = 'o';
char gFoodSymbol = '*';

static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead );
static snakeUnit* add_nodeAtBegining(snakeUnit* pHead, int newHeadRow, int newHeadCol);
static void delete_lastNode(snakeUnit* pHead, int* snakeTailRow, int* snakeTailCol);



snakeUnit* snake_gameInit(char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    snakeUnit *pHead = (snakeUnit *)malloc(sizeof(snakeUnit));

    snake_resetGameScreen(gameScreen);
    srand((unsigned long) time(NULL));
    add_initialSnake(gameScreen, pHead);

    return pHead;
}


void snake_generateFoodPosition(int* const row, int* const col, snakeUnit *pHead)
{   
    snakeUnit *ptr;
    int randNum;
    int generateFlag = 0;

    GENERATE_AGAIN:

    randNum = rand() % SCREEN_ROW ;
    *row = randNum;
    randNum = rand() % SCREEN_COL ;
    *col = randNum;

    ptr = pHead;
    while (ptr != NULL){
        if (ptr->row == *row && ptr->column == *col){
            generateFlag = 1;
            break;
        }
        ptr = ptr->next;
    }
    
    if (generateFlag == 1){
        generateFlag = 0;
        goto GENERATE_AGAIN;
    }
}




bool snake_isEatingFood(int foodRow, int foodColumn, snakeUnit* pHead)
{
    if (pHead->row == foodRow && pHead->column == foodColumn){
        return True;
    }
    return Flase;
}


void snake_increaseSnake(int snakeTailRow, int snakeTailCol, snakeUnit* pHead)
{   
    snakeUnit *newUnit = (snakeUnit *)malloc(sizeof(snakeUnit));
    snakeUnit *ptr = pHead;

    newUnit->row = snakeTailRow;
    newUnit->column = snakeTailCol;
    newUnit->next = NULL;

    while (ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = newUnit;

}



void snake_waitGameScreen(int time)
{
    for (volatile long int i = 0; i < (time * 1000); i++);
}


void snake_addFoodToGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL], const int row, const int col)
{   
    gameScreen[row][col] = gFoodSymbol; 
}


void snake_displayGameScreen(snakeUnit* pHead,  char gameScreen [SCREEN_ROW][SCREEN_COL], int score)
{
    int row = 0;
    int col = 0;

    /*clear screen*/
    system("clear");

    /*print score*/
    printf("      SCORE: %d\n", score);

    /*print game board*/
    printf("----------------------\n");
    for (row = 0; row < SCREEN_ROW; row++){
        printf("|");
        for (col = 0; col < SCREEN_COL; col++){
            printf("%c", gameScreen[row][col]);
            if (col == (SCREEN_COL - 1))
                printf("|");
        }
        if (row != (SCREEN_ROW - 1))
            printf("\n");
    }
    printf("\n----------------------\n");
}



void snake_addSnakeToGameScreen(snakeUnit* pHead, char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    snakeUnit *ptr = pHead;

    /*update game board*/
    while (ptr != NULL){
        gameScreen[ptr->row][ptr->column] = gSnakeSymbol;
        ptr = ptr->next;
    }
}


snakeUnit* snake_updateSnakePosition(char userInput, snakeUnit* pHead, int* snakeTailRow, int* snakeTailCol)
{   
    int headRow = pHead->row;
    int headCol = pHead->column;

    if (userInput == 'w'){
        pHead = add_nodeAtBegining(pHead, (headRow - 1), headCol);
        delete_lastNode(pHead, snakeTailRow, snakeTailCol);

    } else if (userInput == 's'){
        pHead = add_nodeAtBegining(pHead, (headRow + 1), headCol);
        delete_lastNode(pHead, snakeTailRow, snakeTailCol);

    } else if (userInput == 'a'){
        pHead = add_nodeAtBegining(pHead, headRow, (headCol - 1));
        delete_lastNode(pHead, snakeTailRow, snakeTailCol);

    } else if (userInput == 'd'){
        pHead = add_nodeAtBegining(pHead, headRow, (headCol + 1));
        delete_lastNode(pHead, snakeTailRow, snakeTailCol);
    }
    return pHead;
}


void snake_resetGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    int row;
    int col;

    /*reset game board*/
    for (row = 0; row < SCREEN_ROW; row++){
        for (col = 0; col < SCREEN_COL; col++){
            gameScreen[row][col] = gSpace;
        }
    }
}


void snake_updateSocreBoard(int *score)
{
    *score = *score + 10;
}



bool snake_isColliding(snakeUnit *pHead)
{   
    snakeUnit *ptr = pHead->next;
    int headRow = pHead->row;
    int headCol = pHead->column;

    if (headRow == -1 || headRow == SCREEN_ROW){
        return True;

    } else if (headCol == -1 || headCol == SCREEN_COL){
        return True;
    }

    while (ptr != NULL){
        if (ptr->row == headRow && ptr->column == headCol)
            return True;

        ptr = ptr->next;
    }
    return Flase;
}

void snake_terminateGame(char *terminationMsg, int score)
{
    system("clear");
    printf("Your Score: %d\n", score);
    printf("Game Closed: %s\r\n", terminationMsg);
    exit(0);
}


/****** Private Functions ********/

static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    pHead->row = 0;
    pHead->column = 0;
    pHead->next = NULL;

    gameScreen[pHead->row][pHead->column] = gSnakeSymbol;
}


static snakeUnit* add_nodeAtBegining(snakeUnit* pHead, int newHeadRow, int newHeadCol)
{
    snakeUnit* temp = (snakeUnit *)malloc(sizeof(snakeUnit));

    temp->row = newHeadRow;
    temp->column = newHeadCol;
    temp->next = pHead;
    pHead = temp;

    return pHead;
}


static void delete_lastNode(snakeUnit* pHead, int* snakeTailRow, int* snakeTailCol)
{
    snakeUnit* ptr1 = pHead;
    snakeUnit* ptr2 = pHead->next;

    while (ptr2->next != NULL){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    ptr1->next = NULL;

    *snakeTailRow = ptr2->row;
    *snakeTailCol = ptr2->column;
    free(ptr2);
}


// TODO: 1. find a way to to run snake faster with the increasing score [decrease input timeout]