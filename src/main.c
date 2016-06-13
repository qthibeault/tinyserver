#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "logging.h"

int main(int argc, char* argv[])
{
    int port = 8080, sock_desc;
    struct sockaddr_in server;
    
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        log_print(ERROR, "Could not create socket");
        return -1;
    }
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
        log_print(ERROR, "Could not bind socket to port");
        return -1;
    }
    
    log_print(INFO, "Server online at port %d", port);
    
    return 0;
}