/**
 * user2 : programmed as client model
*/

/**
 * User 1 : programmed as server model
*/

/*Included Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFF_SIZE 1024

/*Static Functions Prototype*/
static void error(char *error_message);


/**
 * @brief  : Main logic , Program Entry Point
 * @param  : char *Port_No ( argv[1])
 * @retval : int
 */
int main(int argc, char *argv[])
{   
    /**
     * user is supposed to give port address as cmd-line argument 
     * if not given, throw error
     */
    if (argc < 2){
        error("[-] Port Not Provided\n");
    }

    int socket_fd, connection_status;
    struct sockaddr_in  sock_addr;
    char msgBuffer[BUFF_SIZE];

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0){
        error("[-] Filed Creating Socket\n");
    }
    printf("[+] Socket Successfully Created\n");

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(argv[1]));
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    connection_status =  connect(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if(connection_status < 0){
        error("[-] Connection Error\n");
    }
    printf("[+] Sucessfully Connected To Server\n");

    memset(msgBuffer, 0, BUFF_SIZE);
    strcpy(msgBuffer, "Hello From Client\n");
    send(socket_fd, msgBuffer, BUFF_SIZE, 0);

    memset(msgBuffer, 0, BUFF_SIZE);
    recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
    printf("Server:%s\n", msgBuffer);

    close(socket_fd);
    printf("[-] Connection Closed\n");

    return 0;
}

/**
 * @brief  : Throw error with user defined msg & exit
 * @param  : char *msg
 * @retval : none 
 */
static void error(char *error_message)
{
    perror(error_message);
    exit(1);
}

