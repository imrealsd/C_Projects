#include "snake.h"
#include <unistd.h>
#include <fcntl.h>

/*Global Variables*/
char gameScreen[SCREEN_ROW][SCREEN_COL];
snakeUnit *pSnakeHead;
int foodRow;
int foodCol;
char userInput[2];
char userInputCopy;
int userInputStatus;
int snakeTailRow;
int snakeTailCol;


/*Function Prototypes*/
void changeTerminalBehaviour(void);
void resetTerminalBehaviour(void);
void readUserInput(int timeout);


int main(int argc, char* argv[])
{    
    pSnakeHead = (snakeUnit *)malloc(sizeof(snakeUnit));
    
    /*Initialise Game Screen*/
    snake_gameInit(gameScreen, pSnakeHead);
    snake_generateFoodPosition(&foodRow, &foodCol);
    snake_addFoodToGameScreen(gameScreen, foodRow, foodCol);
    snake_displayGameScreen(pSnakeHead, gameScreen);

    while (True){

        changeTerminalBehaviour();
        readUserInput(1);
        resetTerminalBehaviour();

        pSnakeHead = snake_updateSnakePosition(userInputCopy, pSnakeHead, &snakeTailRow, &snakeTailCol);

        if (snake_isEatingFood(foodRow, foodCol, pSnakeHead)){
            snake_increaseSnake(snakeTailRow, snakeTailCol, pSnakeHead);
            snake_generateFoodPosition(&foodRow, &foodCol);
        }
        snake_resetGameScreen(gameScreen);
        snake_addSnakeToGameScreen(pSnakeHead, gameScreen);
        snake_addFoodToGameScreen(gameScreen, foodRow, foodCol);
        snake_displayGameScreen(pSnakeHead, gameScreen);
    }
    return 0;
}



void readUserInput(int timeout)
{
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    sleep(timeout);
    userInputStatus = read(0, userInput, 2);

    if (userInputStatus != -1){
            userInputCopy = userInput[0];
    } 
}


void changeTerminalBehaviour(void)
{   
    system ("/bin/stty raw");
}


void resetTerminalBehaviour(void)
{   
    system ("/bin/stty cooked");
}


