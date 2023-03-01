#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

#define SCREEN_ROW  10   // height
#define SCREEN_COL  20   // width

typedef enum {

    True  = 1,
    Flase = 0

} bool;

typedef struct snakeUnit {

    int row;
    int column;
    struct snakeUnit *next;

} snakeUnit;


void snake_gameInit(char gameScreen[SCREEN_ROW][SCREEN_COL], snakeUnit* pHead);
void snake_generateFoodPosition(int* const row, int* const col, snakeUnit *pHead);
void snake_addFoodToGameScreen(char gameScreen[SCREEN_ROW][SCREEN_COL], const int row, const int col);
void snake_displayGameScreen(snakeUnit* pHead,  char gameScreen [SCREEN_ROW][SCREEN_COL], int score);
bool snake_isEatingFood(int foodRow, int foodCol, snakeUnit* pHead);
bool snake_isColiding(snakeUnit *pHead);
void snake_increaseSnake(int snakeTailRow, int snakeTailCol, snakeUnit* pHead);
void snake_waitGameScreen(int time);
snakeUnit* snake_updateSnakePosition(char userInput, snakeUnit* pHead, int* snakeTailRow, int* snakeTailCol);
void snake_resetGameScreen(char gameScreen [SCREEN_ROW][SCREEN_COL]);
void snake_addSnakeToGameScreen(snakeUnit* pHead, char gameScreen [SCREEN_ROW][SCREEN_COL]);
void snake_updateSocreBoard(int *score);

#endif