/*Library Includes*/
#include "snake.h"

/*Global variables*/
char gSpace = ' ' ;
char gSnakeSymbol = 'o';
char gFoodSymbol = '*';

/****************Private function prototypes*************************/

/**
 * @brief add single uint primary snake
 */
static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead );

/**
 * @brief add new node at the beginning
 */
static snakeUnit* add_nodeAtBegining(snakeUnit* pHead, int newHeadRow, int newHeadCol);

/**
 * @brief delete last node
 */
static void delete_lastNode(snakeUnit* pHead, int* pSnakeTailRow, int* pSnakeTailCol);

/**
 * @brief clear the terminal
 */
static void clear_terminal(void);



/********************Library functions ******************************/



snakeUnit* snake_gameInit(char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    /*Allocate memory for snake head node*/
    snakeUnit *pHead = (snakeUnit *)malloc(sizeof(snakeUnit));

    /*Reset game screen, initialise seed of rand(..) , add initial snake*/
    snake_resetGameScreen(gameScreen);
    srand((unsigned long) time(NULL));
    add_initialSnake(gameScreen, pHead);

    /*Return address of snake head */
    return pHead;
}


void snake_generateFoodPosition(int* const pRow, int* const pCol, snakeUnit *pHead)
{   
    snakeUnit *ptr;
    int randNum;
    int generateFlag = 0;

    GENERATE_AGAIN:

    /*Generate random row & column*/
    randNum = rand() % SCREEN_ROW ;
    *pRow = randNum;
    randNum = rand() % SCREEN_COL ;
    *pCol = randNum;

    /*Check if the generated row & column is overlaping with the snake body or not*/
    ptr = pHead;
    while (ptr != NULL){
        if (ptr->row == *pRow && ptr->column == *pCol){
            generateFlag = 1;
            break;
        }
        ptr = ptr->next;
    }
    
    /* if overlaping , generate again*/
    if (generateFlag == 1){
        generateFlag = 0;
        goto GENERATE_AGAIN;
    }
}



bool snake_isEatingFood(int foodRow, int foodColumn, snakeUnit* pHead)
{   
    /*Check if snake head position & food position are same or not*/
    if (pHead->row == foodRow && pHead->column == foodColumn){
        return True;
    }
    return Flase;
}


void snake_increaseSnake(int snakeTailRow, int snakeTailCol, snakeUnit* pHead)
{   
    /*Allocate memory for new node*/
    snakeUnit *newUnit = (snakeUnit *)malloc(sizeof(snakeUnit));
    snakeUnit *ptr = pHead;

    /**
     * Add new node the tail of the snake [linked list] 
     * position of new tail node will be last deleted tail node [ given by snake_updatePosition(..) ]
    */
    newUnit->row = snakeTailRow;
    newUnit->column = snakeTailCol;
    newUnit->next = NULL;

    while (ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = newUnit;
}



void snake_addFoodToGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL], const int foodRow, const int foodCol)
{   
    gameScreen[foodRow][foodCol] = gFoodSymbol; 
}


void snake_displayGameScreen(snakeUnit* pHead,  char gameScreen [SCREEN_ROW][SCREEN_COL], int score)
{
    int row = 0;
    int col = 0;

    /*clear screen*/
    clear_terminal();

    /*print score*/
    printf("SCORE: %d\n", score);

    /****print game board****/

    /*Top margin*/
    for (int temp = 0; temp <= SCREEN_COL+1; temp++){
        printf("-");
    }
    printf("\n");

    /*print matrix*/
    for (row = 0; row < SCREEN_ROW; row++){
        printf("|");
        for (col = 0; col < SCREEN_COL; col++){
            printf("%c", gameScreen[row][col]);
            if (col == (SCREEN_COL - 1))
                printf("|");
        }
        printf("\n");
    }

    /*Bottom margin*/
    for (int temp = 0; temp <= SCREEN_COL+1; temp++){
        printf("-");
    }
    printf("\n");
}



void snake_addSnakeToGameScreen(snakeUnit* pHead, char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    snakeUnit *ptr = pHead;

    /*add new snake to game screen*/
    while (ptr != NULL){
        gameScreen[ptr->row][ptr->column] = gSnakeSymbol;
        ptr = ptr->next;
    }
}



snakeUnit* snake_updateSnakePosition(char userInput, snakeUnit* pHead, int* pSnakeTailRow, int* pSnakeTailCol)
{   
    /*Store head position before updating snake position*/
    int headRow = pHead->row;
    int headCol = pHead->column;

    /**
     * snake increasing logic:
     * step 1. add new node at the beginning [row , column will be according to input]
     * step 2. delete last node 
    */

    if (userInput == 'w'){
        /*For inpit 'w', add new node by decresing org. head row by 1 unit [going up]*/
        pHead = add_nodeAtBegining(pHead, (headRow - 1), headCol);
        delete_lastNode(pHead, pSnakeTailRow, pSnakeTailCol);

    } else if (userInput == 's'){
        /*For inpit 's', add new node by incresing org. head row by 1 unit [going down]*/
        pHead = add_nodeAtBegining(pHead, (headRow + 1), headCol);
        delete_lastNode(pHead, pSnakeTailRow, pSnakeTailCol);

    } else if (userInput == 'a'){
        /*For inpit 'a', add new node by decresing org. head column by 1 unit [going left]*/
        pHead = add_nodeAtBegining(pHead, headRow, (headCol - 1));
        delete_lastNode(pHead, pSnakeTailRow, pSnakeTailCol);

    } else if (userInput == 'd'){
        /*For inpit 'd', add new node by decresing org. head column by 1 unit [going right]*/
        pHead = add_nodeAtBegining(pHead, headRow, (headCol + 1));
        delete_lastNode(pHead, pSnakeTailRow, pSnakeTailCol);
    }

    /*return updated new head*/
    return pHead;
}


void snake_resetGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL])
{   
    int row;
    int col;

    /*reset game screen matrix , fill with spaces*/
    for (row = 0; row < SCREEN_ROW; row++){
        for (col = 0; col < SCREEN_COL; col++){
            gameScreen[row][col] = gSpace;
        }
    }
}


void snake_updateSocreBoard(int *pScore)
{   
    int increment = 0;

    /*score increment increases by 5 after every 500 scores*/
    increment = 10 + (5 * ((*pScore)/500));
    *pScore = *pScore + increment;
}



bool snake_isColliding(snakeUnit *pHead)
{   
    snakeUnit *ptr = pHead->next;
    int headRow = pHead->row;
    int headCol = pHead->column;

    /*Check if colliding with the (4) walls*/
    if (headRow == -1 || headRow == SCREEN_ROW){
        return True;

    } else if (headCol == -1 || headCol == SCREEN_COL){
        return True;
    }

    /*Check if colliding with itself*/
    while (ptr != NULL){
        if (ptr->row == headRow && ptr->column == headCol)
            return True;

        ptr = ptr->next;
    }
    return Flase;
}


void snake_terminateGame(char *pTerminationMsg, int score)
{   
    /*Print termination messege , score & terminate program*/
    printf("\n\nYour Score: %d\n", score);
    printf("Game Over: %s\r\n", pTerminationMsg);
    exit(0);
}


void snake_updateSnakeSpeed(int score, long long int* pUsTimeout)
{   
    /* if timeout is 1 ms*/
    if (*pUsTimeout <= 1000){
        return;
    }
    /*Decrese timeout with increasing score : increases speed*/
    *pUsTimeout = (*pUsTimeout - score);
}


/****** Private Functions ********/

static void add_initialSnake(char gameScreen [SCREEN_ROW][SCREEN_COL], snakeUnit* pHead)
{   
    /* add single unit snake to position [0][0]*/
    pHead->row = 0;
    pHead->column = 0;
    pHead->next = NULL;

    gameScreen[pHead->row][pHead->column] = gSnakeSymbol;
}


static snakeUnit* add_nodeAtBegining(snakeUnit* pHead, int newHeadRow, int newHeadCol)
{   
    /*Allocate memory for new node*/
    snakeUnit* temp = (snakeUnit *)malloc(sizeof(snakeUnit));

    /*Add new node at the beginning, update head*/
    temp->row = newHeadRow;
    temp->column = newHeadCol;
    temp->next = pHead;
    pHead = temp;

    /*return new head*/
    return pHead;
}


static void delete_lastNode(snakeUnit* pHead, int* pSnakeTailRow, int* pSnakeTailCol)
{
    snakeUnit* ptr1 = pHead;
    snakeUnit* ptr2 = pHead->next;

    /*delete last node*/
    while (ptr2->next != NULL){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    ptr1->next = NULL;

    /**
     * store position (row,col) of deleted node
     * required for increasing the snake after eating food
    */
    *pSnakeTailRow = ptr2->row;
    *pSnakeTailCol = ptr2->column;

    /*free memory of deleted node*/
    free(ptr2);
}


static void clear_terminal(void)
{
    system("clear");
}

// TODO: 1. find a way to to run snake faster with the increasing score [decrease input timeout]