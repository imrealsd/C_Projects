#ifndef SERVER_H
#define SERVER_H
void setup_server(char *port);
void waitFor_client(void);
void get_input(char *num1, char *num2, int* choice);
void send_output(char *result);
void close_connection(void);

#endif // !SERVER_H