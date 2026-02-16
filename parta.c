#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    for(int i = 1; i < argc; i++){
        // capitalize each letter
        char *arg = argv[i];
        // loop individual character
        for(int x = 0; arg[x] != '\0'; x++){
            arg[x] = toupper(arg[x]);
        }
        printf("%s", arg);
        if(i < argc -1){
            printf(",");
        }
    }
    printf("\n");
    return 0;
}
