#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];
    pid_t child_pid;
    char buffer[256];

    if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
        perror("pipe");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_parent_to_child[1]);   // Close write end of parent-to-child pipe
        close(pipe_child_to_parent[0]);   // Close read end of child-to-parent pipe

        ssize_t bytes_read = read(pipe_parent_to_child[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }

        printf("Child process received: %s\n", buffer);

        const char *response = "Hello, parent process!";
        ssize_t bytes_written = write(pipe_child_to_parent[1], response, strlen(response));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        close(pipe_parent_to_child[0]);
        close(pipe_child_to_parent[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe_parent_to_child[0]);   // Close read end of parent-to-child pipe
        close(pipe_child_to_parent[1]);   // Close write end of child-to-parent pipe

        const char *message = "Hello, child process!";
        ssize_t bytes_written = write(pipe_parent_to_child[1], message, strlen(message));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        ssize_t bytes_read = read(pipe_child_to_parent[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }

        printf("Parent process received: %s\n", buffer);

        close(pipe_parent_to_child[1]);
        close(pipe_child_to_parent[0]);
        wait(NULL);
    }

    return 0;
}
