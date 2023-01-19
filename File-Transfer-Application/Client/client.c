
/*Included Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFF_SIZE 1024

/*Static Functions Prototype*/
static void error(char *error_message);
static void receive_file(void);
static void setup_connection(char *);

/*Global variables*/
int socket_fd, connection_status;
struct sockaddr_in  sock_addr;
char msgBuffer[BUFF_SIZE];
int8_t sub_div_flag = 0;
int cont = 1;

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

    setup_connection(argv[1]);
    receive_file();
    close(socket_fd);
    printf("[-] Disconnected\n");
    return 0;
}

/**
 * @brief  :receieve & write file data
 * @param  :none
 * @retval :none
*/
static void receive_file(void)
{
    FILE *fp;
    uint8_t byte_count = 0;
    uint8_t buff[1];

    fp = fopen("file.txt","w");

    /*recv file size in bytes*/
    recv(socket_fd, &byte_count, 1, 0);

    while (byte_count--){
        if(recv(socket_fd, buff, 1, 0) == -1){
            error("[-] Failed to receive file\n");
        }
        fputc(buff[0], fp);
    }
    printf("[+] File Successfully Received\n");
    fclose(fp);
}


/**
 * @brief  : setup socket , bind with port , connect to server
 * @param  : char* port
 * @retval : none
 */
static void setup_connection(char * port)
{
   
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0){
        error("[-] Filed Creating Socket\n");
    }
    printf("[+] Socket Successfully Created\n");

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(port));
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    /*Program waits @ conect func until handshake is done with srever: [if Non Blocking Mode is used]*/
    connection_status =  connect(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if(connection_status < 0){
        error("[-] Connection Error\n");
    }
    printf("[+] Sucessfully Connected\n");
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
