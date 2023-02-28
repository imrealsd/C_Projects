#include "snake.h"

char gSpace = ' ' ;
char gsnakeSymbol = 'o';
char gFoodSymbol = '*';

static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead );
static snakeUnit* add_nodeAtBegining(snakeUnit* pHead, int newHeadRow, int newHeadCol);
static void delete_lastNode(snakeUnit* pHead, int* snakeTailRow, int* snakeTailCol);



void snake_gameInit(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    snake_resetGameScreen(gameScreen);
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


void snake_clearGameScreen(void)
{   
    system("clear");
}


void snake_waitGameScreen(int time)
{
    for (volatile long int i = 0; i < (time * 1000); i++);
}


void snake_addFoodToGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL], const int row, const int col)
{   
    gameScreen[row][col] = gFoodSymbol; 
}


void snake_displayGameScreen(snakeUnit* pHead,  char gameScreen [SCREEN_ROW][SCREEN_COL])
{
    int row = 0;
    int col = 0;

    /*clear screen*/
    system("clear");

    /*print game board*/
    printf("\n----------------------\n");
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
        gameScreen[ptr->row][ptr->column] = gsnakeSymbol;
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



/****** Private Functions ********/

static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    pHead->row = 0;
    pHead->column = 0;
    gameScreen[pHead->row][pHead->column] = gsnakeSymbol;
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


// TODO: 1. Add collision rules
//       2. Add score board
//       3. Add game termination input key
//       4. Run snake automatically [make input timeout] [:: Done] 
//       5. take care of food position if generated inside snake 