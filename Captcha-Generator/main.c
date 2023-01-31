/*public includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*private includes*/
#include "captcha.h"


int main(int argc, char* argv[])
{   
    // Arrays for storing cpatchas
    char systemCaptcha[GEN_CAP_SIZE];
    char userInputCaptcha[GEN_CAP_SIZE];

    /**
     * Generate captcha
     * Display captcha
     * Take user input
     * Comapre / match systemCaptcha with userInputCaptcha
     */
    captcha_generateCaptcha(systemCaptcha);
    captcha_displayCaptcha(systemCaptcha);
    captcha_takeUserInput(userInputCaptcha);

    if (captcha_isCaptchaMatched(systemCaptcha, userInputCaptcha)){
        printf("Captcha verified !!\n");
    } else {
        printf("\nWrong captcha !!\n");
    }
    return 0;
}
