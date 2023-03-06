/* Library Includes */
#include "main.h"
 

/*Global Variables*/
snakeUnit *pSnakeHead;
char gameScreen[SCREEN_ROW][SCREEN_COL];
char userInput[2];
char gUserInputCopy;
int  gFoodRow;
int  gFoodCol;
int  gUserInputStatus;
int  gSnakeTailRow;
int  gSnakeTailCol;
int  gScore = 0;
long long int gUsTimeout = DEFAULT_TIMEOUT;


/* Private Function Prototypes */
static void changeTerminalBehaviour(void);
static void resetTerminalBehaviour(void);
static void readUserInput(long long int usTimeout);



/**
 * @brief Program entry Point
 */
int main(int argc, char* argv[])
{    
    /*Initialise Game, add snake , add food & display game screen*/
    pSnakeHead = snake_gameInit(gameScreen);
    snake_generateFoodPosition(&gFoodRow, &gFoodCol, pSnakeHead);
    snake_addFoodToGameScreen(gameScreen, gFoodRow, gFoodCol);
    snake_displayGameScreen(pSnakeHead, gameScreen, gScore);

    while (True){
        
        /*Get input form user*/
        readUserInput(gUsTimeout);
        
        /*Terminate game if input is 'q'*/
        if (userInput[0] == 'q'){
            snake_terminateGame("Exit Button Pressed\n", gScore);
        }

        /*Update snake position according to user input*/
        pSnakeHead = snake_updateSnakePosition(gUserInputCopy, pSnakeHead, &gSnakeTailRow, &gSnakeTailCol);
        
        /*Terminate game if the snake is colliding with the walls or with itself*/
        if (snake_isColliding(pSnakeHead)){
            snake_terminateGame("Collision\n", gScore);
        
        /* If snake is eating the food, increase snake, update score, generate new food*/
        } else if (snake_isEatingFood(gFoodRow, gFoodCol, pSnakeHead)){
            
            snake_increaseSnake(gSnakeTailRow, gSnakeTailCol, pSnakeHead);
            snake_updateScoreBoard(&gScore);
            snake_updateSnakeSpeed(gScore, &gUsTimeout);
            snake_generateFoodPosition(&gFoodRow, &gFoodCol, pSnakeHead);
        }

        /*Reset game screen , add snake, add food , display game screen*/
        snake_resetGameScreen(gameScreen);
        snake_addSnakeToGameScreen(pSnakeHead, gameScreen);
        snake_addFoodToGameScreen(gameScreen, gFoodRow, gFoodCol);
        snake_displayGameScreen(pSnakeHead, gameScreen, gScore);
    }

    return 0;
}



/**
 * @brief read user input from keyboard
*/
static void readUserInput(long long int usTimeout)
{    
    changeTerminalBehaviour();

    /*setup for user input with a fixed timeout*/
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    usleep(usTimeout);
    gUserInputStatus = read(0, userInput, 2);

    resetTerminalBehaviour();

    /*if there's an input*/
    if (gUserInputStatus != -1){
        
        /*take only valid inputs*/
        if (userInput[0] == 'w' || userInput[0] == 's' || userInput[0] == 'a' || 
                                    userInput[0] == 'd' || userInput[0] == 'q'){

            gUserInputCopy = userInput[0];
        } 
    } 
}


/**
 * @brief change terminal behaviour to 'raw' [take input without pressing 'Enter' key]
*/
static void changeTerminalBehaviour(void)
{   
    system ("/bin/stty raw");
}

/**
 * @brief reset terminal to normal input mode 
*/
static void resetTerminalBehaviour(void)
{   
    system ("/bin/stty cooked");
}


