#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int run_program(const char *executable,
                const char *input_file,
                const char *output_file) {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // Open input file
        int input = open(input_file, O_RDONLY);

        if (input < 0) {
            perror("input file");
            exit(1);
        }

        // Open output file
        int output = open(output_file,
                           O_WRONLY | O_CREAT | O_TRUNC,
                           0644);

        if (output < 0) {
            perror("output file");
            exit(1);
        }

        // Redirect standard input
        dup2(input, STDIN_FILENO);

        // Redirect standard output
        dup2(output, STDOUT_FILENO);

        close(input);
        close(output);

        // Replace child process with submitted program
        execl(executable, executable, (char *)NULL);

        perror("exec failed");
        exit(1);
    }

    // Parent waits for child
    int status;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return -1;
}
