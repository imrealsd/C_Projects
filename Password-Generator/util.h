/*Define Driver*/
#ifndef UTIL_H
#define UTIL_H

/*Macros*/
#define MAX_PASS_LEN 101  // 100 digit password + 1 null char
#define TOTAL_LETTER 26
#define TOTTAL_NUM 10
#define TOTAL_SPL_CHAR 20

/**
 * @brief  get password length according to password index
 * @param  int password index
 * @return int password length
 */
int  util_getPasswordLength(int passIndex);

/**
 * @brief  store password in text file
 * @param  char* password
 * @return none
 */
void storePasswordInText(const char* const password);

/**
 * @brief  display generated password
 * @param  char* passoword
 * @return  none
 */
void util_displayGeneratedPassword(const char* const password);

/**
 * @brief generate passoword of user defined length
 * @param char* pGeneratedPassoword (to store password), int password length
 * @return none
 */
void util_generatePassword(char* const pGeneratedPassword, const int passwordLength);

#endif //  UTIL_H