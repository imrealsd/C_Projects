#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"
#define BUFF_SIZE 1

/*private function prototypes*/
static void error(char*);

/*Global variables*/
uint8_t msgbuff[BUFF_SIZE];
struct sockaddr_in server_addr, client_addr;
int server_fd, client_fd, bind_status;
socklen_t addr_size;


/**
 * @brief  : setup socket , bind with port
 * @param  : char *port
 * @retval : none
 */
void setup_server(char *port)
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0){
        error("[-] Filed Creating Socket\n");
    }
    printf("[+] Socket Successfully Created\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    bind_status = bind(server_fd,(struct sockaddr*) &server_addr, sizeof(server_addr));
    if (bind_status < 0){
        error("[-] Binding Error\n");
    }
    printf("[+] Successfully Binded To Port\n");
}

/**
 * @brief  : put server in listen mode & wait for client to approach
 * @param  : none
 * @retval : none
 */
void wait_for_client(void)
{
    listen(server_fd, 1);
    memset(&client_addr, 0, sizeof(client_addr));

    /* program waits @ accept func until client request arrives [if Non Blocking Mode is not used]*/
    client_fd = accept(server_fd,(struct sockaddr*)&client_addr, &addr_size);
    printf("[+] Client Connected\n\n");
}


/**
 * @brief  : throw error with messege
 * @param  : char *messege
 * @retval : none
 */
static void error(char *msg)
{
    perror(msg);
    exit(1);
}


/**
 * @brief  : send text file to client
 * @param  : none
 * @retval : none
 */
void send_file(void)
{   
    /**
     * First send File size [by counting characters] to client
     * Then transmit file [1byte frame]
    */
    FILE *fp;
    uint8_t byte_count = 0;  /*max 255 byte file can be sent in this config*/
    char ch;

    if ((fp = fopen("file.txt", "r")) == NULL){
        error("[-]Failed to open file\n");
    }

    /**
     * calculate file size
     * send file size to client
     * send file 1 byte per frame
     */
    while ((ch = fgetc(fp)) != EOF){
        byte_count++;
    }

    msgbuff[0] = byte_count;
    send(client_fd, msgbuff, BUFF_SIZE, 0);

    rewind(fp);

    while (byte_count--){
        ch = fgetc(fp);
        msgbuff[0] = ch;
        if (send(client_fd,msgbuff, BUFF_SIZE, 0) == -1){
            error("[-] Error Sending File\n");
        }
    }
    printf("[+] File Successfully Sent\n");
    fclose(fp);
}


/**
 * @brief  : close client socket
 * @param  : none
 * @retval : none
 */
void close_client_connection(void)
{
    close(client_fd);
    printf("[-] Client Disconnected\n");
}