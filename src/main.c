#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "logging.h"

#define D_PORT 8080

int main(int argc, char* argv[])
{
    int port = D_PORT;
    int sock_desc, client_desc;
    socklen_t client_size;
    struct sockaddr_in server;
    struct sockaddr_storage client;
    pid_t pid;

    if (argc > 1) {
        port = atoi(argv[1]);
    }
    
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
    log_print(INFO, "Awaiting incoming connections...");

    client_size = sizeof(client_desc);
    while ((client_desc = accept(sock_desc, (struct sockaddr*)&client, &client_size)))
    {
        char s[15];
        inet_ntop(client.ss_family, &((struct sockaddr_in*)&client)->sin_addr, s, sizeof s);

        if((pid = fork()) < 0) {
            log_print(ERROR, "could not fork");
        }
        else {
            if (pid == 0) {
                close(sock_desc);

                char buffer[8096];
                read(client_desc, buffer, 8097);
                char* method = strtok(buffer, " ");
                char* path = strtok(NULL, " ");
                log_print(INFO, "%s request on path %s from %s", method, path, s);

                if (strlen(path) == 1) {
                    path = "";
                }
                char *fname = malloc(sizeof(char) * (strlen(path) + 2));
                strcat(strcpy(fname, "."), path);
                
                struct stat sb;
                if (stat(fname, &sb) == 0 && S_ISDIR(sb.st_mode)) {
                    fname = realloc(fname, sizeof(char) * (strlen(fname) + 12));
                    strcat(fname, "/index.html");
                }
                
                if (access(fname, F_OK) != -1) {
                    write(client_desc, "HTTP/1.1 200 OK\n", 16);
                    write(client_desc, "Content-length: 46\n", 19);
                    write(client_desc, "Content-Type: text/html\n\n", 25);
                    write(client_desc, "<html><body><H1>Hello world</H1></body></html>", 46);
                }
                else {
                    write(client_desc, "HTTP/1.1 404 NOT FOUND\n", 16);
                    write(client_desc, "Content-length: 48\n", 19);
                    write(client_desc, "Content-Type: text/html\n\n", 25);
                    write(client_desc, "<html><body><H1>404 Not Found</H1></body></html>", 48);
                }

                free(fname);
                exit(1);
            }
            else {
                close(client_desc);
            }
        }
    }

    if(client_desc < 0) {
        close(sock_desc);
        log_print(ERROR, "Could not accept connection");
        exit(1);
    }

    close(client_desc);
    close(sock_desc);
    exit(0);
}