#ifndef UTIL_H
#define UTIL_H

#define MAX_PASS_LEN 101  // 100 digit password + 1 null char
#define TOTAL_LETTER 26
#define TOTTAL_NUM 10
#define TOTAL_SPL_CHAR 20

int  util_getPasswordLength(void);
void util_displayWelcomeMessege(const char* const msg);
void util_displayGeneratedPassword(const char* const password);
void util_generatePassword(char* const pGeneratedPassword, const int passwordLength);

#endif //  UTIL_H