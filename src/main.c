#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "logging.h"

int create_socket(int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return sockfd;
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = port;
    
    return bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
}

int main(int argc, char *argv[])
{
    int port = 80;
    
    /* Parse argument flags */
    int i;
    for(i = 1; i < argc - 1; ++i){
        char *arg = argv[i];
        if(arg[0] == '-'){
            switch(arg[1]){
                case 'p': {
                    port = atoi(argv[++i]);
                }
            }
        }
    }
    
    /* Create Server */
    int server = create_socket(port);
    if (server < 0) {
        log_print(ERROR, "Could not create socket on port %d", port);
        exit(-1);
    }
    
    /* Tell server to start listening */
    listen(server, 10);
    log_print(INFO, "Created socket on port: %d", port);
    
    int conn;
    char buffer[256];
    while (1) {
        conn = accept(server, (struct sockaddr*)NULL, NULL);
        printf("Opened connection");
        
        snprintf(buffer, sizeof(buffer), "Connection recieved");
        write(conn, buffer, strlen(buffer));
        
        close(conn);
        sleep(1);
    }
    
    return 0;
}
