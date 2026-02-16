#include <stdbool.h>
#include <stddef.h>

// DO YOU KNOW HOW MUCH WORK I HAD TO DO TO LEARN ALL THIS!!! D:
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {

    // TODO: Complete and document
    if (argc == 1){
        const char msg[] = "ERROR: no arguments\n";
        write(1, msg, sizeof(msg) - 1);
        return 1;
    }
    if (argc != 3){
        const char msg[] = "USAGE: ./partc <word> <file>\n";
        write(1, msg, sizeof(msg) - 1);
        return 1;
    }
    const char *word = argv[1];
    const char *file = argv[2];
    pid_t pid = fork();

    if (pid < 0){
        perror("fork");
        return 1;

    }

    if (pid == 0){
        char *eargs[] = {
            (char *)"grep",
            (char *)"-s",
            (char *)"-q",
            (char *)word,
            (char *)file,
            NULL
        };

        execv("/usr/bin/grep", eargs);

        perror("exec");
        _exit(1);

    }

    // Parent function
    int status = 0;
    if (waitpid(pid, &status, 0) < 0){
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)){
        int code = WEXITSTATUS(status);

        if (code == 0){
            const char prefix[] = "FOUND: ";
            write(1, prefix, sizeof(prefix) - 1);
            size_t len = 0;
            while (word[len] != '\0') len++;
            write(1, word, len);
            write(1, "\n", 1);

            return 0;
        }

        if (code == 2){
            const char prefix[] = "ERROR: ";
            write(1, prefix, sizeof(prefix) - 1);

            size_t len = 0;
            while (file[len] != '\0') len++;
            write(1, file, len);
            const char suffix[] = " doesn't exist\n";
            write(1, suffix, sizeof(suffix) - 1);

            return 2;

        }

        const char msg[] = "ERROR\n";
        write(1, msg, sizeof(msg) - 1);
        return 2;
    }

    // At this point the child ain't exist... so basically all of this was for nothing... D:

    const char msg[] = "ERROR\n";
    write(1, msg, sizeof(msg) - 1);
    return 2;



    return 0;
}
