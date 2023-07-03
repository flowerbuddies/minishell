#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av, char **envp) {
    int pipefd[2];

    pid_t pid;
    char buffer[256];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
		printf("child: %d,%d\n", pipefd[0], pipefd[1]);
		sleep(3);
		write(pipefd[1], "child", 6);
		printf("---->%s\n", envp[0]);
        exit(0);
    } else {
        // Parent process
		printf("parent: %d,%d\n", pipefd[0], pipefd[1]);
		char *just_read = malloc(6);
		read(pipefd[0], just_read, 6);
		printf("parent: %s\n", just_read);
        wait(NULL);  // Wait for the child process to finish
    }

    return 0;
}
