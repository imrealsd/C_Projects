/*Header includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

/**
 * @brief  : program entry point
 * @param  : char  *port
 * @retval : int 
 */
int main(int argc, char *argv[])
{   
    if (argc < 2){
        printf("Port not provided.\n");
        return 1;
    }
    setup_server(argv[1]);

    while (1){
        wait_for_client();
        send_file();
        close_client_connection();
    }
    return 0;
}