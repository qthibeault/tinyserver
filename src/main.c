#include <stdio.h>
#include <stdlib.h>

#include "logging.h"

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
    
    log_print(INFO, "Bringing up server on port: %d", port);
    return 0;
}
