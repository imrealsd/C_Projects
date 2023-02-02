/*public header includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*private header includes*/
#include "util.h"

/*private function prototypes*/

/**
 * @brief  shuffle generated password
 * @param  char* passoword
 * @return  none
 */
static void util_shufflePassword(char *password);


/*capital letttes, small letters, special character & num arrays used to generate password*/
char capitalLetters[TOTAL_LETTER] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                          'Q','R','S','T','U','V','W','X','Y','Z'};

char smallLetters[TOTAL_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                        'r','s','t','u','v','w','x','y','z'};

char numbers[TOTTAL_NUM] = {'0','1','2','3','4','5','6','7','8','9'};

char specialCharacters[TOTAL_SPL_CHAR] = {'!','#','$','%','^','&','*','(',')','~','<','>',',','.','?',
                              '{','}','[',']','|'};




int util_getPasswordLength(int passIndex)
{   
    int passwordLength;
    /*Get password length from the user*/
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

    //initialize temppassword & pGeneratedPassword array
    memset(pGeneratedPassword, 0, MAX_PASS_LEN);
    memset(tempPassword, 0, MAX_PASS_LEN);

    /**
     * one iteraton of while loop generate 4 digit password
     * if password length is multiple of 4 , run the loop for (password length / 4) times
     * else run nearest multiple of 4 (bigger than password length) times
     */
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

    /**
     * take 4 cpu clock values to generate 4 index of 4 different password elements
     * store them into tempPassword
     * shuffle them after the loop terminates
     * copy passwordLength num of elemets of tempPassword to pGeneratedPassoword  (final)
     */
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
    util_shufflePassword(tempPassword);
    strncpy(pGeneratedPassword, tempPassword, passwordLength);
}


void util_displayGeneratedPassword(const char* const password)
{
    // print generated password on console
    printf("Password: %s\n\n", password);
}


void storePasswordInText(const char* const password)
{
    FILE* pFile;
    static int count = 1;
    
    /**
     * at the first time of password generation :
     * remove prev password file
     * add new blank file
     * write file header text
     */
    if (count == 1){
        remove("passwords.txt");
        pFile = fopen("passwords.txt", "w");
        fputs("Generated Passwords:\n\n", pFile);
        fclose(pFile);
    }
    /*write generated password along with it's index num in text file*/
    pFile = fopen("passwords.txt", "a");
    fputs("password_", pFile);
    // put index of password
    fprintf(pFile, "%d", count++);
    fputs(": ", pFile);
    // put password
    fputs(password, pFile);
    fputc('\n', pFile);
    // close file
    fclose(pFile);
}


static void util_shufflePassword(char *password)
{   
    char subString1[MAX_PASS_LEN];
    char subString2[MAX_PASS_LEN];
    int  len = strlen(password);
    int subLen1 = len/2;
    int subLen2 = (len - subLen1);
    int i = 0;
    int j = 0;
    int k = 0;

    /*initialise two su strings */
    memset(subString1, 0, MAX_PASS_LEN);
    memset(subString2, 0, MAX_PASS_LEN);
    /*split the password into 2 different subarrays of size (len/2) & (len - (len/2))*/
    strncpy(subString1, password, (subLen1));
    strncpy(subString2, (password + (subLen1)), subLen2);

    /*take one element form each subarray and put them one after another in final passoword , like card shuffling*/
    while ((i < len) && (j < subLen2) && (k < subLen1)){
        password[i++] = subString2[j++];
        password[i] = subString1[k++];
    }
    // if len is odd (len - (len/2)) is 1 element bigger than (len/2) , put the last element into final password
    if (len % 2)
        password[i] = subString2[j];
}