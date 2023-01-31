#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*define driver*/
#ifndef CAPTCHA_H
#define CAPTCHA_H

/*defines*/
#define TOTAL_NUM 10
#define TOTAL_LETTER 26
#define TOTAL_SPL_CHAR 20
#define ARITHMATIC_CAP_SIZE 9           // ex. "99-99 = ?"
#define ALPHANUMERIC_CAP_SIZE 5         // ex. "G2j#1"
#define GEN_CAP_SIZE 10                 // 9 char + 1 null char
#define TOTAL_OPERATION 2
#define MIN_THREE_DIG_NUM 100
#define ASCII_OFFSET_VAL 48

/**
 * @brief generate a alphanumerical or arithmatic captcha
 * @param char* chaptcha 
 * @retval none 
 */
void captcha_generateCaptcha(char* captcha);

/**
 * @brief take input from user 
 * @param char* userInputCaptcha
 * @retval none 
 */
void captcha_takeUserInput(char *userInputCaptcha);

/**
 * @brief display genearted captcha in nice box
 * @param char* chaptcha 
 * @retval none 
 */
void captcha_displayCaptcha(const char* const captcha);

/**
 * @brief match user captcha with system generated captcha
 * @param char* systemCaptcha, char* userInputChaptcha, 
 * @retval int 
 */
int  captcha_isCaptchaMatched(char* systeCaptcha, char* userInputCaptcha);

#endif //  CAPTCHA_H