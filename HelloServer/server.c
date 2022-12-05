#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define ERROR -1
#define DONE 0

void error_handling(char const *msg) {
    write(STDERR, "Error :", 7);
    if (msg) write(STDERR, msg, strlen(msg));
    write(STDERR, "\n", 1);
    exit(ERROR);
}

int main(int argc, char **argv) {
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;

    char *msg = "Hello! Client!";

    if (argc != 2)
        error_handling("Usage - ./server [port]");

    if ((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == ERROR)
        error_handling("sock() was failed.");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == ERROR)
        error_handling("bind() was failed.");
    
    if (listen(serv_sock, 5) == ERROR)
        error_handling("listen() was failed.");
    
    client_addr_size = sizeof(client_addr);
    client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock == ERROR)
        error_handling("accept() was failed.");

    write(client_sock, msg, strlen(msg));
    close(client_sock);
    close(serv_sock);
    return 0;
}

