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
 * @brief  : Main Logic , Program Entry Point
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

    int server_sock_descriptor, client_sock_descriptor, bind_status;
    struct sockaddr_in  server_addr, client_addr;
    socklen_t addr_size;
    char msgBuffer[BUFF_SIZE];

    server_sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_descriptor < 0){
        error("[-] Filed Creating Socket\n");
    }
    printf("[+] Socket Successfully Created\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    bind_status = bind(server_sock_descriptor,(struct sockaddr*) &server_addr, sizeof(server_addr));
    if (bind_status < 0){
        error("[-] Binding Error\n");
    }
    printf("[+] Successfully Binded IP & Port\n");

    listen(server_sock_descriptor, 5);

    while (1){

        memset(&client_addr, 0, sizeof(client_addr));

        /* program waits @ accept func until client request arrives*/
        client_sock_descriptor = accept(server_sock_descriptor,(struct sockaddr*)&client_addr, &addr_size);
        printf("[+] Connected\n");

        memset(msgBuffer, 0, sizeof(msgBuffer));
        recv(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
        printf("Client: %s\n", msgBuffer);

        memset(msgBuffer, 0, sizeof(client_addr));
        strcpy(msgBuffer, "Hello From Server\n");
        send(client_sock_descriptor, msgBuffer, strlen(msgBuffer), 0);

        close(client_sock_descriptor);
        printf("[-] Disconnected\n");
    }
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

