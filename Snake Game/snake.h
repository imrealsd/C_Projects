/* Public Headers */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/********Library Definitation***********/

#ifndef SNAKE_H
#define SNAKE_H

/*Constants*/
#define SCREEN_ROW  20              // board height 
#define SCREEN_COL  40              // board width  
#define  DEFAULT_TIMEOUT 500000     // in us (control snake speed)

/* Enum for bool */
typedef enum {

    True  = 1,
    Flase = 0

} bool;


/* Structure for storing the position of one single unit of snake*/
typedef struct snakeUnit {

    int row;
    int column;
    struct snakeUnit *next;

} snakeUnit;


/************************* Libray API's Prototypes***************************/

/**
 * @brief  initialise the game 
 * @param  gameScreen 2D matrix
 * @return snakeUnit*
 */
snakeUnit* snake_gameInit(char gameScreen[SCREEN_ROW][SCREEN_COL]);


/**
 * @brief  update snake position according to user input , store the last tail position of the snake
 * @param   userInput       input form user
 * @param   pHead           pointer to head node of the snake [linked list] 
 * @param   pSnakeTailRow   pointer for storing last tail position row of the snake
 * @param   pSnakeTailCol   pointer for storing last tail position col of the snake
 * @return snakeUnit*
 */
snakeUnit* snake_updateSnakePosition(char userInput, snakeUnit* pHead, int* pSnakeTailRow, int* pSnakeTailCol);


/**
 * @brief  check if the snake is eating the food or not  
 * @param  foodRow row of food position
 * @param  foodCol column of food position
 * @param  pHead   pointer to head node of the snake [linked list]
 * @return bool (True / False )
 */
bool snake_isEatingFood(int foodRow, int foodCol, snakeUnit* pHead);


/**
 * @brief  check if the snake is colliding with the walls or with itself 
 * @param  pHead pointer to head node of the snake [linked list]
 * @return bool (True / False)
 */
bool snake_isColliding(snakeUnit *pHead);


/**
 * @brief  generate new food position
 * @param  pRow pointer to variable that stores row of generated food position 
 * @param  pCol pointer to variable that stores column of generated food position 
 * @param  pHead pointer to head node of the snake [linked list]
 * @return void 
 */
void snake_generateFoodPosition(int* const pRow, int* const pCol, snakeUnit *pHead);


/**
 * @brief  add food to game screen
 * @param  gameScreen 2D matrix
 * @param  foodRow row of generated food's position 
 * @param  foodCol column of generated food's position 
 * @return void
 */
void snake_addFoodToGameScreen(char gameScreen[SCREEN_ROW][SCREEN_COL], const int foodRow, const int foodCol);

/**
 * @brief  display game screen 
 * @param  pHead pointer to head node of the snake [linked list]
 * @param  gameScreen 2D matrix
 * @param  score last score
 * @return void
 */
void snake_displayGameScreen(snakeUnit* pHead,  char gameScreen [SCREEN_ROW][SCREEN_COL], int score);


/**
 * @brief  display game screen 
 * @param  snakeTailRow last (deleted) row position of snake tail
 * @param  snakeTailCol last (deleted) column position of snake tail
 * @param  pHead pointer to head node of the snake [linked list]
 * @return void
 */
void snake_increaseSnake(int snakeTailRow, int snakeTailCol, snakeUnit* pHead);


/**
 * @brief  reset game screen matrix
 * @param  gameScreen 2D matrix
 * @return void
 */
void snake_resetGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL]);


/**
 * @brief  add updated sanke to game screen
 * @param  pHead pointer to head node of the snake [linked list]
 * @param  gameScreen 2D matrix
 * @return void
 */
void snake_addSnakeToGameScreen(snakeUnit* pHead, char gameScreen [SCREEN_ROW][SCREEN_COL]);


/**
 * @brief  update score board
 * @param  score last score.
 * @return void
 */
void snake_updateSocreBoard(int *score);


/**
 * @brief terminate game.
 * @param pTerminationMsg pointer to termination messege to be shown.
 * @param score last score.
 * @return void
 */
void snake_terminateGame(char *pTerminationMsg, int score);

/**
 * @brief update snake by decreasing input timeout
 * @param score last score.
 * @param pUsTimeout pointer to usTimeout variable
 * @return void
 */
void snake_updateSnakeSpeed(int score, long long int* pUTimeout);

/*******************************************************************************/

#endif