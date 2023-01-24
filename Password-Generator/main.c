#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.h"

int main(int argc, char *argv[])
{
    char password[MAX_PASS_LEN];
    int  passLen;
    int  passCount;
    int  passIndex = 1;

    printf("\n--Welcome to Password Generator--\n\n");
    printf("Enter Number of Password You want to Generate:");
    scanf("%d", &passCount);
    
    while (passCount--){
        passLen = util_getPasswordLength(passIndex++);
        util_generatePassword(password, passLen);
        storePasswordInText(password);
    }
    printf("\nPassword Generation Completed\n");
    return 0;
}
