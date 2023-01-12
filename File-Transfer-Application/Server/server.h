#ifndef SERVER_H
#define SERVER_H
void setup_server(char *port);
void wait_for_client(void);
void send_file(void);
void close_client_connection(void);
#endif // !1 "SERVER_H" 