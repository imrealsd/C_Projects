#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

#define SCREEN_ROW  20   // height
#define SCREEN_COL  20   // width

typedef enum {

    True  = 1,
    Flase = 0

} bool;

typedef struct {

    int row;
    int column;
    struct snakeUnit *next;

} snakeUnit;



void snake_gameInit(char gameScreen[SCREEN_ROW][SCREEN_COL], snakeUnit* pHead);
void snake_generateFoodPosition(int* const row, int* const col);
void snake_clearGameScreen(char gameScreen[SCREEN_ROW][SCREEN_COL]);
void snake_addFoodToGameScreen(char gameScreen[SCREEN_ROW][SCREEN_COL], const int row, const int col);
void snake_displayGameScreen(char gameScreen[SCREEN_ROW][SCREEN_COL]);
bool snake_isEatingFood(int foodRow, int foodCol, snakeUnit* pHead);

#endif