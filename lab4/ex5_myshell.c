#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64

int main() {
    char command[256];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            // End of input (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // If user just presses Enter, keep going
        if (strlen(command) == 0) {
            continue;
        }

        // Exit command
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Tokenize input into argv array
        char *argv[MAX_ARGS];
        int argc = 0;

        char *token = strtok(command, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;  // execvp needs NULL-terminated argv

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            continue;
        }

        if (pid == 0) {
            // CHILD: run the command
            execvp(argv[0], argv);

            // If execvp returns, it failed
            perror("Command execution failed");
            exit(1);
        } else {
            // PARENT: wait for child
            wait(NULL);
        }
    }

    return 0;
}
