#include "main.h"

/*Global Variables*/
char gameScreen[SCREEN_ROW][SCREEN_COL];
snakeUnit *pSnakeHead;
int  gFoodRow;
int  gFoodCol;
char userInput[2];
char gUserInputCopy;
int  gUserInputStatus;
int  gSnakeTailRow;
int  gSnakeTailCol;
int  gScore = 0;


/*Function Prototypes*/
void changeTerminalBehaviour(void);
void resetTerminalBehaviour(void);
void readUserInput(int timeout);
void terminateGame(void);


int main(int argc, char* argv[])
{    
    pSnakeHead = (snakeUnit *)malloc(sizeof(snakeUnit));
    
    /*Initialise Game Screen*/
    snake_gameInit(gameScreen, pSnakeHead);
    snake_generateFoodPosition(&gFoodRow, &gFoodCol);
    snake_addFoodToGameScreen(gameScreen, gFoodRow, gFoodCol);
    snake_displayGameScreen(pSnakeHead, gameScreen, gScore);

    while (True){

        readUserInput(1);
        if (userInput[0] == 'q')
            terminateGame();

        pSnakeHead = snake_updateSnakePosition(gUserInputCopy, pSnakeHead, &gSnakeTailRow, &gSnakeTailCol);

        if (snake_isEatingFood(gFoodRow, gFoodCol, pSnakeHead)){
            snake_increaseSnake(gSnakeTailRow, gSnakeTailCol, pSnakeHead);
            snake_updateSocreBoard(&gScore);
            snake_generateFoodPosition(&gFoodRow, &gFoodCol);
        }
        snake_resetGameScreen(gameScreen);
        snake_addSnakeToGameScreen(pSnakeHead, gameScreen);
        snake_addFoodToGameScreen(gameScreen, gFoodRow, gFoodCol);
        snake_displayGameScreen(pSnakeHead, gameScreen, gScore);
    }
    return 0;
}



void readUserInput(int timeout)
{    
    changeTerminalBehaviour();

    /*setup for user input with a fixed timeout*/
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    sleep(timeout);
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


void terminateGame(void)
{
    system("clear");
    printf("Game Closed\r\n");
    exit(0);
}

void changeTerminalBehaviour(void)
{   
    system ("/bin/stty raw");
}


void resetTerminalBehaviour(void)
{   
    system ("/bin/stty cooked");
}


