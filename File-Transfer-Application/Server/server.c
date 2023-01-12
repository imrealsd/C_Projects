#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"
#define BUFF_SIZE 1024

char msgbuff[BUFF_SIZE];
struct sockaddr_in server_addr, client_addr;
int server_fd, client_fd;
socklen_t addr_size;

void setup_server(char *port)
{

}


void wait_for_client(void)
{

}


void error(char *msg)
{
    perror(msg);
    exit(1);
}