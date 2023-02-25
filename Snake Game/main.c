#include "snake.h"

/*Global Variables*/
char gameScreen[SCREEN_ROW][SCREEN_COL];
snakeUnit *pSnakeHead;
char userInput;


/*Function Prototypes*/
void changeTerminalBehaviour(void);


int main(int argc, char* argv[])
{    
    /*change terminal behaviour to take input without pressing enter*/
    changeTerminalBehaviour();
    
    /*Initialise Game Screen*/
    snake_gameInit(gameScreen, pSnakeHead);
    snake_displayGameScreen(gameScreen);

    while (True){
        userInput = getchar();
        break;
    }
    return 0;
}


void changeTerminalBehaviour(void)
{
    system ("/bin/stty raw");
}