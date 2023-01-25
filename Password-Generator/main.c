/*public includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*private util lib includes*/
#include "util.h"


/**
 * @brief program entry point
 */
int main(int argc, char *argv[])
{
    char password[MAX_PASS_LEN];
    int  passLen;
    int  passCount;
    int  passIndex = 1;

    /*print welcome, take number of passoword user want to generate*/
    printf("\n--Welcome to Password Generator--\n\n");
    printf("Enter Number of Password You want to Generate:");
    scanf("%d", &passCount);
    
    /*take length of each password , generate & store into text file*/
    while (passCount--){
        passLen = util_getPasswordLength(passIndex++);
        util_generatePassword(password, passLen);
        storePasswordInText(password);
    }
    printf("\nPassword Generation Completed\n");
    return 0;
}
