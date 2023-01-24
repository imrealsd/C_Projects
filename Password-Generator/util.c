#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"


char capitalLetters[TOTAL_LETTER] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                          'Q','R','S','T','U','V','W','X','Y','Z'};

char smallLetters[TOTAL_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                        'r','s','t','u','v','w','x','y','z'};

char numbers[TOTTAL_NUM] = {'0','1','2','3','4','5','6','7','8','9'};

char specialCharacters[TOTAL_SPL_CHAR] = {'!','#','$','%','^','&','*','(',')','~','<','>',',','.','?',
                              '{','}','[',']','|'};


void util_displayWelcomeMessege(const char* const msg)
{
    printf("%s\n", msg);
}

int util_getPasswordLength(int passIndex)
{   
    int passwordLength;

    printf("Enter Password_%d Length (min 4 & max 100) :", passIndex);
    scanf("%d", &passwordLength);

    return passwordLength;
}


 
void util_generatePassword(char* const pGeneratedPassword, const int passwordLength)
{   
    char tempPassword[MAX_PASS_LEN];
    int capLetIndex;
    int smallLetIndex;
    int splCharIndex;
    int numIndex;
    int passIndex = 0;
    int loopCount;
    clock_t time;

    memset(pGeneratedPassword, 0, MAX_PASS_LEN);
    memset(tempPassword, 0, MAX_PASS_LEN);

    if (passwordLength % 4){
        for (int multiplier = 1; multiplier <= 25; multiplier++){
            int temp = (4 * multiplier);
            if ((temp - passwordLength) > 0){
                loopCount = multiplier;
                break;
            }
        }
    } else {
        loopCount = (passwordLength / 4);
    }


    //TODO: add more randomness to password [different seq of nums, letters, spclchars etc]
    while (loopCount--){

        time  = clock();
        capLetIndex   = (time % TOTAL_LETTER);
        time = clock();
        splCharIndex = (time % TOTAL_SPL_CHAR);
        time = clock();
        numIndex = (time % TOTTAL_NUM);
        time = clock();
        smallLetIndex = (time % TOTAL_LETTER);

        tempPassword[passIndex++] = capitalLetters[capLetIndex];
        tempPassword[passIndex++] = numbers[numIndex];
        tempPassword[passIndex++] = specialCharacters[splCharIndex];
        tempPassword[passIndex++] = smallLetters[smallLetIndex];
    }
    strncpy(pGeneratedPassword, tempPassword, passwordLength);
}


void util_displayGeneratedPassword(const char* const password)
{
    printf("Password: %s\n\n", password);
}


void storePasswordInText(const char* const password)
{
    FILE* pFile;
    static int count = 1;
    
    if (count == 1){
        remove("passwords.txt");
        pFile = fopen("passwords.txt", "w");
        fputs("Generated Passwords:\n\n", pFile);
        fclose(pFile);
    }

    pFile = fopen("passwords.txt", "a");
    fputs("password_", pFile);
    fprintf(pFile, "%d", count++);
    fputs(": ", pFile);

    fputs(password, pFile);
    fputc('\n', pFile);

    fclose(pFile);
}

