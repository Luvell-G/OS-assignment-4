#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Fork failed
        printf("Fork failed\n");
    }
    else if (pid == 0) {
        // Child process
        printf("I am the child process. PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    }
    else {
        // Parent process
        printf("I am the parent process. PID = %d, Child PID = %d\n",
               getpid(), pid);
    }

    return 0;
}
