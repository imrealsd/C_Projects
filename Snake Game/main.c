#include "snake.h"

/* Game main screen */
char gameScreen[SCREEN_ROW][SCREEN_COL];

int main(int argc, char* argv[])
{   
    snake_addFoodToScreen(gameScreen, 10, 20);
    return 0;
}