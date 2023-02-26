#include "snake.h"

/*Global Variables*/
char gameScreen[SCREEN_ROW][SCREEN_COL];
snakeUnit *pSnakeHead;
int foodRow;
int foodCol;
char userInput;


/*Function Prototypes*/
void changeTerminalBehaviour(void);


int main(int argc, char* argv[])
{    
    pSnakeHead = (snakeUnit *)malloc(sizeof(snakeUnit));
    /*change terminal behaviour to take input without pressing enter*/
    //changeTerminalBehaviour();
    
    /*Initialise Game Screen*/
    snake_gameInit(gameScreen, pSnakeHead);
    snake_generateFoodPosition(&foodRow, &foodCol);
    snake_addFoodToGameScreen(gameScreen, foodRow, foodCol);
    snake_displayGameScreen(pSnakeHead, gameScreen);

    while (True){

        userInput = getchar();
        pSnakeHead = snake_updateSnakePosition(userInput, pSnakeHead);

        if (snake_isEatingFood(foodRow, foodCol, pSnakeHead)){
            pSnakeHead = snake_increaseSnake(pSnakeHead, foodRow, foodCol);
            snake_generateFoodPosition(&foodRow, &foodCol);
        }
        snake_resetGameScreen(gameScreen);
        snake_addSnakeToGameScreen(pSnakeHead, gameScreen);
        snake_addFoodToGameScreen(gameScreen, foodRow, foodCol);
        snake_displayGameScreen(pSnakeHead, gameScreen);
    }
    return 0;
}


void changeTerminalBehaviour(void)
{
    system ("/bin/stty raw");
}