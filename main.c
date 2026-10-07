#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "runner.h"
#include "judge.h"

int main() {

    int choice;

    printf("UNIX MINI JUDGE\n");
    printf("----------------\n");

    /* Display available problems */

    printf("Available Problems:\n");
    printf("1. Sum of Two Numbers\n");
    printf("2. Find Maximum\n");

    printf("\nEnter problem number: ");
    scanf("%d", &choice);

    /* Select problem directory */

    const char *problem_directory;

    if (choice == 1) {
        problem_directory = "problems/problem1";
    }
    else if (choice == 2) {
        problem_directory = "problems/problem2";
    }
    else {
        printf("Invalid problem number.\n");
        return 1;
    }

    /* Display selected problem */

    printf("\n----- Problem -----\n");

    char problem_file[200];

    snprintf(problem_file, sizeof(problem_file),
             "%s/problem.txt",
             problem_directory);

    FILE *file = fopen(problem_file, "r");

    if (file == NULL) {
        printf("Unable to open problem file.\n");
        return 1;
    }

    char line[500];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);

    printf("-------------------\n");

    /* Get solution file from user */

    char solution_file[200];

    printf("\nEnter solution file path: ");
    scanf("%199s", solution_file);

    /* Compile user's solution */

    char compile_command[400];

    snprintf(compile_command, sizeof(compile_command),
             "gcc \"%s\" -o submissions/temp_solution",
             solution_file);

    printf("\nCompiling submission...\n");

    int compile_status = system(compile_command);

    if (compile_status != 0) {
        printf("Result: COMPILATION ERROR\n");
        return 1;
    }

    printf("Compilation successful.\n");

    /* Find test cases automatically */

    printf("\nRunning test cases...\n");

    DIR *dir = opendir(problem_directory);

    if (dir == NULL) {
        printf("Unable to open problem directory.\n");
        return 1;
    }

    struct dirent *entry;

    int passed = 0;
    int total_tests = 0;

    while ((entry = readdir(dir)) != NULL) {

        /* Only process .in files */

        char *input_extension = strstr(entry->d_name, ".in");

        if (input_extension == NULL) {
            continue;
        }

        /* Create input file path */

        char input_path[300];

        snprintf(input_path, sizeof(input_path),
                 "%s/%s",
                 problem_directory,
                 entry->d_name);

        /* Create corresponding .out filename */

        char output_name[256];

        snprintf(output_name, sizeof(output_name),
                 "%s",
                 entry->d_name);

        char *extension = strstr(output_name, ".in");

        if (extension != NULL) {
            strcpy(extension, ".out");
        }

        /* Create expected output file path */

        char expected_path[300];

        snprintf(expected_path, sizeof(expected_path),
                 "%s/%s",
                 problem_directory,
                 output_name);

        total_tests++;

        printf("\nTest Case %d:\n", total_tests);

        /* Run submitted program */

        int status = run_program(
            "./submissions/temp_solution",
            input_path,
            "test_cases/actual.out"
        );

        /* Check for runtime error */

        if (status != 0) {
            printf("Result: RUNTIME ERROR\n");
            continue;
        }

        /* Compare actual output with expected output */

        int result = compare_output(
            "test_cases/actual.out",
            expected_path
        );

        if (result == 1) {
            printf("Result: ACCEPTED\n");
            passed++;
        }
        else {
            printf("Result: WRONG ANSWER\n");
        }
    }

    closedir(dir);

    /* Display final result */

    printf("\n----------------\n");
    printf("Tests Passed: %d/%d\n", passed, total_tests);

    if (total_tests > 0 && passed == total_tests) {
        printf("Final Result: ACCEPTED\n");
    }
    else {
        printf("Final Result: WRONG ANSWER\n");
    }

    return 0;
}
