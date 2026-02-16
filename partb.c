#include <stdbool.h>
#include <stddef.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    int n = argc - 1;
    
    // So you said not to use printf so had to tweak it here
    if (n == 0){
        const char msg[] = "ERROR: no arguments\n";
        write(1, msg, sizeof(msg) - 1);
        return 1;
    }

    // Echo buildup

    char *eargs[4];
    eargs[0] = "echo";

    // Add single or multiple
    if (n % 2 == 1){
        int mid = n / 2;
        eargs[1] = argv[1 + mid];
        eargs[2] = NULL;
    }else{
        int mid1 = (n / 2) - 1;
        int mid2 = (n / 2);
        eargs[1] = argv[1 + mid1];
        eargs[2] = argv[1 + mid2];
        eargs[3] = NULL;
    }

    int eret = execv("/bin/echo", eargs);
    if (eret == -1){
        perror("exec");
        return 1;
    }

    return 0;


}
