#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H

#define SCREEN_ROW  50   // height
#define SCREEN_COL  50   // width

void snake_addFoodToScreen(char* const gameScreen, const int row, const int col);

#endif