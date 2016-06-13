#include <stdlib.>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "logging.h"

int main(int argc, char* argv[])
{
    int sock_desc;
    struct sockaddr_in server;
    
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        log_print(ERROR, "Could not create socket");
        return -1;
    }
    
    return 0;
}