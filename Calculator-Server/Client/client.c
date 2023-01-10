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
static void display_result(char *result, int size);
static void communicate_with_server(void);
static void setup_connection(char *);

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

    while (cont){

        communicate_with_server();

        printf("\nwant to coninue ? [y/n]:");
        getchar();
        char stat = getchar();
    }

    close(socket_fd);
    printf("[-] Disconnected\n");

    return 0;
}



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



static void communicate_with_server(void)
{
    /*NUM_1*/
    memset(msgBuffer, 0, BUFF_SIZE);
    recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
    printf("CAL-SERVER: %s\n", msgBuffer);

    memset(msgBuffer, 0, BUFF_SIZE);
    printf("ME: ");
    scanf("%s", msgBuffer);
    send(socket_fd, msgBuffer, BUFF_SIZE, 0);

    /*NUM2*/
    memset(msgBuffer, 0, BUFF_SIZE);
    recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
    printf("CAL-SERVER: %s\n", msgBuffer);

    memset(msgBuffer, 0, BUFF_SIZE);
    printf("ME: ");
    scanf("%s", msgBuffer);
    send(socket_fd, msgBuffer, BUFF_SIZE, 0);

    /*OPERATON*/
    memset(msgBuffer, 0, BUFF_SIZE);
    recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
    printf("CAL-SERVER: %s\n", msgBuffer);

    memset(msgBuffer, 0, BUFF_SIZE);
    printf("ME: ");
    scanf("%s", msgBuffer);
    send(socket_fd, msgBuffer, BUFF_SIZE, 0);

    if (msgBuffer[0] == 47 || msgBuffer[0] == 45)
        sub_div_flag = 1;
    
    /**
     * RESULT
     * 1 output for add & multiply
     * 2 output for subtraction : sign & value
     * 2 output for quotient & remainder
     */

    memset(msgBuffer, 0, BUFF_SIZE);
    recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
    printf("CAL-SERVER: ");
    display_result(msgBuffer, BUFF_SIZE);

    /*if sub or div operation*/
    if (sub_div_flag == 1){
        
        memset(msgBuffer, 0, BUFF_SIZE);
        recv(socket_fd, msgBuffer, BUFF_SIZE, 0);
        printf(" ");
        display_result(msgBuffer, BUFF_SIZE);
    }
    sub_div_flag = 0;
    printf("\n");
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

/**
 * @brief  Display result after calculation
 * @retval none
 */
static void display_result(char *result, int size)
{   
   
    int first_num_encountered_flag = 0;

    /*print only after the first non zero element is found*/
    for (int i = 0; i < size; i++){
        
        if (result[i] != '0')
            first_num_encountered_flag = 1;

        if (first_num_encountered_flag == 1)
            printf("%c", result[i]);
    }
}