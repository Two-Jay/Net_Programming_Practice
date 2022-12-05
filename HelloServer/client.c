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

#define BUFFER_SIZE 50

void error_handling(char const *msg) {
    write(STDERR, "Error :", 7);
    if (msg) write(STDERR, msg, strlen(msg));
    write(STDERR, "\n", 1);
    exit(ERROR);
}


// 클라이언트 코드
// 클라이언트에서는 socket() - connect() 순으로 진행
int main(int argc, char **argv) {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    int str_len;

    if (argc != 3)
        error_handling("Usage - ./client [IP] [port]");

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == ERROR)
        error_handling("sock() was failed.");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == ERROR)
        error_handling("connect() was failed.");
    
    str_len = read(sock, buffer, sizeof(buffer) - 1);
    if (str_len == ERROR)
        error_handling("read() was failed");

    printf("Server : %s\n", buffer);
    close(sock);
    return DONE;
}
