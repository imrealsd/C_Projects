#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.h"

int main(int argc, char *argv[])
{
   
    const char* const msg = "\n\n--Welcome To Password Generator--\n\n";
    char password[MAX_PASS_LEN];
    int len;

    util_displayWelcomeMessege(msg);
    len = util_getPasswordLength();
    util_generatePassword(password, len);
    util_displayGeneratedPassword(password);

    return 0;
}
