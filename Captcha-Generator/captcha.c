#include "captcha.h"
#include <time.h>
static int is_odd(time_t num);
static void captcha_generateAlphanumeric(char* captcha);
static void captcha_generateArithmatic(char* captcha);


/*capital letttes, small letters, special character & num arrays used to generate captcha*/
char capitalLetters[TOTAL_LETTER] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                          'Q','R','S','T','U','V','W','X','Y','Z'};

char smallLetters[TOTAL_LETTER] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                        'r','s','t','u','v','w','x','y','z'};

char numbers[TOTAL_NUM] = {'0','1','2','3','4','5','6','7','8','9'};

char specialCharacters[TOTAL_SPL_CHAR] = {'!','#','$','%','^','&','*','(',')','~','<','>',',','.','?',
                              '{','}','[',']','|'};

char operation[TOTAL_OPERATION] = {'+', '-'};


void captcha_generateCaptcha(char* captcha)
{   
    char arithmaticCaptcha[ARITHMATIC_CAP_SIZE];
    char alphaNumericCaptcha[ALPHANUMERIC_CAP_SIZE];
    time_t randNum = clock();

    memset(captcha, 0, GEN_CAP_SIZE);
    memset(arithmaticCaptcha, 0, ARITHMATIC_CAP_SIZE);
    memset(alphaNumericCaptcha, 0, ALPHANUMERIC_CAP_SIZE);

    if (is_odd(randNum)){
        captcha_generateAlphanumeric(alphaNumericCaptcha);
        strncpy(captcha, alphaNumericCaptcha, ALPHANUMERIC_CAP_SIZE);
    } else {
        captcha_generateArithmatic(arithmaticCaptcha);
        strncpy(captcha, arithmaticCaptcha, ARITHMATIC_CAP_SIZE);
    }
}

static int is_odd(time_t num)
{
    if (num % 2){
        return 1;
    }
    return 0;
}


static void captcha_generateAlphanumeric(char* captcha)
{
    time_t randNum = clock();

    captcha[0] = smallLetters[(randNum % TOTAL_LETTER)];
    captcha[1] = numbers[(randNum % TOTAL_NUM)];
    captcha[2] = capitalLetters[(randNum % TOTAL_LETTER)];
    captcha[3] = specialCharacters[(randNum % TOTAL_SPL_CHAR)];
    captcha[4] = numbers[(randNum % TOTAL_NUM)];
}



static void captcha_generateArithmatic(char* captcha)
{
    time_t randNum;
    int num1;
    int num2;
    int opIndex;

    randNum = clock();
    num1 = (randNum % MIN_THREE_DIG_NUM);
    randNum = clock();
    opIndex = (randNum % TOTAL_OPERATION);
    randNum = clock();
    num2 = ((3 *randNum) % MIN_THREE_DIG_NUM);
    
    
    captcha[1] = ((num2 / 10) % 10) + 48;
    captcha[0] = (num2 % 10) + 48;
    captcha[2] = operation[opIndex];
    captcha[4] = ((num1 / 10) % 10) + 48;
    captcha[3] = (num1 % 10) + 48;
    captcha[5] = ' ';
    captcha[6] = '=';
    captcha[7] = ' ';
    captcha[8] = '?';
}

void captcha_displayCaptcha(const char* const captcha)
{   
    char *alphaNumSpacePadding  =  "    " ;
    char *arithmaticSpacePadding = " " ;

    printf("\n --Captcha--\n");
    printf("----------------\n");
    printf("|              |\n");

    if (strlen(captcha) == ALPHANUMERIC_CAP_SIZE)
        printf("|    %s %s|\n", captcha, alphaNumSpacePadding);
    else
        printf("|    %s%s|\n", captcha, arithmaticSpacePadding);

    printf("|              |\n");
    printf("----------------\n");
}


void captcha_takeUserInput(char *userInputCaptcha)
{
    printf("Type Here:");
    scanf("%s", userInputCaptcha);
}


int captcha_isCaptchaMatched(char* systeCaptcha, char* userInputCaptcha)
{   
    int num1;
    int num2;
    int result;
    int usrResult;

    if (strlen(systeCaptcha) == ALPHANUMERIC_CAP_SIZE){

        if (strncmp(systeCaptcha, userInputCaptcha, (GEN_CAP_SIZE-1))){
            return 1;
        }
        return 0;

    } else if (strlen(systeCaptcha) == ARITHMATIC_CAP_SIZE) {

        num1 = ((systeCaptcha[0] - 48) * 10) + (systeCaptcha[1] - 48);
        num2 = ((systeCaptcha[3] - 48) * 10) + (systeCaptcha[4] - 48);
        usrResult = ((userInputCaptcha[0] - 48) * 10) + (userInputCaptcha[1] - 48);

        if (systeCaptcha[2] == '+'){
            result = num1 + num2;
        } else {
            result = num1 - num2;
        }

        if (result == usrResult){
            return 1;
        }
        return 0;
    }
    return 0;
}



// TODO 1. Take typed captcha form user 
//      2. match user typed captcha with system generated captcha
//      3. write main() func 
