#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

char capitalLetters[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                          'Q','R','S','T','U','V','W','X','Y','Z'};

char smallLetters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                        'r','s','t','u','v','w','x','y','z'};

char numbers[10] = {'1','2','3','4','5','6','7','8','9'};

char specialCharacters[20] = {'!','#','$','%','^','&','*','(',')','~','<','>',',','.','?','{','}','[',']','|'};


void welcomeMessege(const char* const msg)
{
    printf("%s\b", msg);
}

int getPasswordLength(void)
{   
    int passwordLength;

    printf("Enter Password Length:");
    scanf("%d", &passwordLength);

    return passwordLength;
}

void generatePassword(char* const pGeneratedPassword, int passwordLength)
{

}


