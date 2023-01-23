#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.h"

int main(int argc, char *argv[])
{
    char password[MAX_PASS_LEN];
    int len;

    util_displayWelcomeMessege("-------Welcome To Password Generator-----\n\n");
    len = util_getPasswordLength();
    util_generatePassword(password, len);
    util_displayGeneratedPassword(password);

    return 0;
}
