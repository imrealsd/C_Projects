#include "captcha.h"
#include <time.h>

/**
 * @brief check if a number is odd or even
 * @param time_t(long)  num
 * @retval int
 */
static int is_odd(time_t num);

/**
 * @brief swap two integers
 * @param  int* num1, int* num2 
 * @retval none 
 */
static void swap(int* num1, int* num2);

/**
 * @brief generate a alphanumerical captcha
 * @param char* chaptcha 
 * @retval none 
 */
static void captcha_generateAlphanumeric(char* captcha);

/**
 * @brief generate a arithmatic captcha
 * @param char* chaptcha 
 * @retval none 
 */
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

    /*initialize all array elemets to zero*/
    memset(captcha, 0, GEN_CAP_SIZE);
    memset(arithmaticCaptcha, 0, ARITHMATIC_CAP_SIZE);
    memset(alphaNumericCaptcha, 0, ALPHANUMERIC_CAP_SIZE);

    /**
     * Generate alphanumeric captcha if randNumm is odd , else genearte arithmatic captcha
     * copy generated captcha into user passed array (char* captcha)
    */
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
    /**
     * generate 5 randum numbers for 5 indexes
     * 1 for capital letter
     * 1 for small letter
     * 2 for numbers
     * 1 for special charcter
     * put them into alphanumericCaptcha array
     */
    time_t randNum = clock();
    captcha[0] = smallLetters[(randNum % TOTAL_LETTER)];
    randNum = clock();
    captcha[1] = numbers[(randNum % TOTAL_NUM)];
    randNum = clock();
    captcha[2] = capitalLetters[(randNum % TOTAL_LETTER)];
    randNum = clock();
    captcha[3] = specialCharacters[(randNum % TOTAL_SPL_CHAR)];
    randNum = clock();
    captcha[4] = numbers[(randNum % TOTAL_NUM)];
}



static void captcha_generateArithmatic(char* captcha)
{
    time_t randNum;
    int num1;
    int num2;
    int opIndex;
    int temp;

    /*generate two (2-digit) numbers & operation symbol ('+','-)*/
    randNum = clock();
    num1 = (randNum % MIN_THREE_DIG_NUM);
    randNum = clock();
    opIndex = (randNum % TOTAL_OPERATION);
    randNum = clock();
    num2 = ((3 *randNum) % MIN_THREE_DIG_NUM);

    /**
     * swap num1 & num2 if num1 > num2 to make sure num2 is always bigger than num1
     * This is to avoid negative result i.e num2-num1 = always +ve
     */
    if (num1 > num2){
       swap(&num1, &num2);
    }
    
    /*put [num1][operation symbol][num1][space]['='][space]['?'] into arithmaticCpatcha array*/
    captcha[1] = ((num2 / 10) % 10) + ASCII_OFFSET_VAL;
    captcha[0] = (num2 % 10) + ASCII_OFFSET_VAL;
    captcha[2] = operation[opIndex];
    captcha[4] = ((num1 / 10) % 10) + ASCII_OFFSET_VAL;
    captcha[3] = (num1 % 10) + ASCII_OFFSET_VAL;
    captcha[5] = ' ';
    captcha[6] = '=';
    captcha[7] = ' ';
    captcha[8] = '?';
}

static void swap(int* num1, int* num2)
{
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}


void captcha_displayCaptcha(const char* const captcha)
{   
    char *alphaNumSpacePadding  =  "    " ;
    char *arithmaticSpacePadding = " " ;

    /*print captcha insside a nice box*/
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
    memset(userInputCaptcha, 0, GEN_CAP_SIZE);
    printf("Type Here: ");
    scanf("%s", userInputCaptcha);
}


int captcha_isCaptchaMatched(char* systeCaptcha, char* userInputCaptcha)
{   
    int num1;
    int num2;
    int result;
    int usrResult = 0;
    int index = 0;

    /*incase of alphanumeric captcha just compare the string & return 1 (match) or 0 (no match)*/
    if (strlen(systeCaptcha) == ALPHANUMERIC_CAP_SIZE){

        if (!strncmp(systeCaptcha, userInputCaptcha, ALPHANUMERIC_CAP_SIZE)){
            return 1;
        }
        return 0;

    /**
     * incase of arithmatic captcha, extract num1,num2,operation symbol form system captcha
     * extract user input (useResult) from userInputcaptcha
     * calculate result of num1[operatiin][num2]
     * compare result with userResult
     * return 0 (wrong input) 1 (correct input)
     */
    } else if (strlen(systeCaptcha) == ARITHMATIC_CAP_SIZE) {

        num1 = ((systeCaptcha[0] - ASCII_OFFSET_VAL) * 10) + (systeCaptcha[1] - ASCII_OFFSET_VAL);
        num2 = ((systeCaptcha[3] - ASCII_OFFSET_VAL) * 10) + (systeCaptcha[4] - ASCII_OFFSET_VAL);

        // extarct user input result
        while (userInputCaptcha[index] != 0){
            usrResult = (usrResult * 10) + (userInputCaptcha[index] - ASCII_OFFSET_VAL);
            index++;
        }

        // extarct operation
        if (systeCaptcha[2] == '+'){
            result = num1 + num2;
        } else {
            result = num1 - num2;
        }
        // comapre user & system result
        if (result == usrResult){
            return 1;
        }
        return 0;
    }
    return 0;
}

