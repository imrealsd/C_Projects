/**
 * User 1 : programmed as server model
*/

/*Included Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <server.h>
#define BUFF_SIZE 1024

/*Static Functions Prototype*/
static void error(char *error_message);


/*Global Variables*/
int server_sock_descriptor, client_sock_descriptor, bind_status;
struct sockaddr_in  server_addr, client_addr;
socklen_t addr_size;
char msgBuffer[BUFF_SIZE];

/**
 * @brief : create socket & bind port 
 * @param : char*
 * @retval: none
 */
void setup_server(char *port)
{   

    server_sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_descriptor < 0){
        error("[-] Filed Creating Socket\n");
    }
    printf("[+] Socket Successfully Created\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    bind_status = bind(server_sock_descriptor,(struct sockaddr*) &server_addr, sizeof(server_addr));
    if (bind_status < 0){
        error("[-] Binding Error\n");
    }
    printf("[+] Successfully Binded To Port\n");
}

/**
 * @brief : listen & wait for client
 * @param : none
 * @retval: none
 */
void waitFor_client(void){

    listen(server_sock_descriptor, 1);
    memset(&client_addr, 0, sizeof(client_addr));

    /* program waits @ accept func until client request arrives [if Non Blocking Mode is not used]*/
    client_sock_descriptor = accept(server_sock_descriptor,(struct sockaddr*)&client_addr, &addr_size);
    printf("[+] Successfully Connected\n");

}

/**
 * @brief :  get input form  client
 * @param : char* char * int*
 * @retval: none
 */
void get_input(char *num1, char *num2, int *operation){
        
    memset(msgBuffer, 0, sizeof(msgBuffer));
    strcpy(msgBuffer, "send 1st number:");
    send(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    memset(msgBuffer, 0, sizeof(msgBuffer));
    recv(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    strcpy(num1, msgBuffer);

    memset(msgBuffer, 0, sizeof(msgBuffer));
    strcpy(msgBuffer, "send 2nd number:");
    send(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    memset(msgBuffer, 0, sizeof(msgBuffer));
    recv(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    strcpy(num2, msgBuffer);

    memset(msgBuffer, 0, sizeof(msgBuffer));
    strcpy(msgBuffer, "send operation:");
    send(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    memset(msgBuffer, 0, sizeof(msgBuffer));
    recv(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0);
    
    switch (msgBuffer[0]){
        case '+':
            *operation = 1;
            break;
        case '-':
            *operation = 2;
            break;
        case '*':
            *operation = 3;
            break;
        case '/':
            *operation = 4;
            break;
    }

    if (strcmp(msgBuffer, "BYE\n") == 0){
        close_connection();
        printf("[-] Client Disconnected\n");
    }
}


/**
 * @brief : send result to client
 * @param : char*
 * @retval: none
 */
void send_output(char *result)
{   
    memset(msgBuffer, 0, sizeof(msgBuffer));
    strcpy(msgBuffer, result);
    send(client_sock_descriptor, msgBuffer, sizeof(msgBuffer), 0); 
}

/**
 * @brief  : close connection with client
 * @param  : none
 * @retval : none 
 */
void close_connection(void)
{
    close(client_sock_descriptor);
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

