#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CAPTCHA_H
#define CAPTCHA_H

#define TOTAL_NUM 10
#define TOTAL_LETTER 26
#define TOTAL_SPL_CHAR 20
#define ARITHMATIC_CAP_SIZE 9           // ex. 99-99 = ?
#define ALPHANUMERIC_CAP_SIZE 5         // 5 char 
#define GEN_CAP_SIZE 10                 // 9 char + 1 null char
#define TOTAL_OPERATION 2
#define MIN_THREE_DIG_NUM 100


void captcha_generateCaptcha(char* captcha);
void captcha_takeUserInput(char *userInputCaptcha);
void captcha_displayCaptcha(const char* const captcha);
int  captcha_isCaptchaMatched(char* systeCaptcha, char* userInputCaptcha);

#endif //  CAPTCHA_H