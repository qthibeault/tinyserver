#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int port = 80;
    
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
    
    printf("Bringing server online on port %d\n", port);
    return 0;
}
