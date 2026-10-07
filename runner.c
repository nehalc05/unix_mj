#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define TIME_LIMIT 2

int run_program(const char *executable,
                const char *input_file,
                const char *output_file) {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {

        int input = open(input_file, O_RDONLY);

        if (input < 0) {
            perror("input file");
            exit(1);
        }

        int output = open(output_file,
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

        if (output < 0) {
            perror("output file");
            exit(1);
        }

        dup2(input, STDIN_FILENO);
        dup2(output, STDOUT_FILENO);

        close(input);
        close(output);

        execl(executable, executable, (char *)NULL);

        perror("exec failed");
        exit(1);
    }

    time_t start_time = time(NULL);

    while (1) {

        int status;

        pid_t result = waitpid(pid, &status, WNOHANG);

        if (result == pid) {

            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            }

            return -1;
        }

        if (result == -1) {
            return -1;
        }

        if (difftime(time(NULL), start_time) >= TIME_LIMIT) {

            kill(pid, SIGKILL);

            waitpid(pid, NULL, 0);

            return -2;
        }

        usleep(100000);
    }
}
