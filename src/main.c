#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "logging.h"

#define D_PORT 8080

int main(int argc, char* argv[])
{
    int port = D_PORT;
    int sock_desc, client_desc;
    socklen_t client_size;
    struct sockaddr_in server, client;
    
    sock_desc = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        log_print(ERROR, "Could not create socket");
        exit(1);
    }
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
        log_print(ERROR, "Could not bind socket to port");
        exit(1);
    }
    listen(sock_desc, 3);
    
    log_print(INFO, "Server online at port %d", port);

    client_size = sizeof(client_desc);
    client_desc = accept(sock_desc, (struct sockaddr*)&client, &client_size);
    
    char *msg = "HTTP/1.1 200 OK\nContent-Type:text/plain\n\nHello World\n";
    send(client_desc, msg, strlen(msg), 0);

    close(client_desc);
    close(sock_desc);
    
    return 0;
}