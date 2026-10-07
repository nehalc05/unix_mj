#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "runner.h"
#include "judge.h"

#define MAX_TESTS 100

/* Compare test case filenames */
int compare_test_cases(const void *a, const void *b) {

    const char *file1 = *(const char **)a;
    const char *file2 = *(const char **)b;

    int number1 = 0;
    int number2 = 0;

    sscanf(file1, "test%d.in", &number1);
    sscanf(file2, "test%d.in", &number2);

    return number1 - number2;
}
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

    /* Get solution file */

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

    /* Open problem directory */

    printf("\nRunning test cases...\n");

    DIR *dir = opendir(problem_directory);

    if (dir == NULL) {
        printf("Unable to open problem directory.\n");
        return 1;
    }

    struct dirent *entry;

    /* Store test case filenames */

    char *test_cases[MAX_TESTS];

    int test_count = 0;

    while ((entry = readdir(dir)) != NULL) {

        int length = strlen(entry->d_name);

        /* Check whether filename ends with .in */

        if (length < 3 ||
            strcmp(entry->d_name + length - 3, ".in") != 0) {
            continue;
        }

        if (test_count >= MAX_TESTS) {
            printf("Too many test cases.\n");
            break;
        }

        test_cases[test_count] = malloc(strlen(entry->d_name) + 1);

        if (test_cases[test_count] == NULL) {
            printf("Memory allocation failed.\n");
            closedir(dir);
            return 1;
        }

        strcpy(test_cases[test_count], entry->d_name);

        test_count++;
    }

    closedir(dir);

    /* Sort test cases */

    qsort(
        test_cases,
        test_count,
        sizeof(char *),
        compare_test_cases
    );

    int passed = 0;
    int wrong_answers = 0;
    int runtime_errors = 0;
    int time_limit_exceeded=0;
    /* Run test cases */

    for (int i = 0; i < test_count; i++) {

        char input_path[300];

        snprintf(input_path, sizeof(input_path),
                 "%s/%s",
                 problem_directory,
                 test_cases[i]);

        /* Create expected output filename */

        char output_name[256];

        snprintf(output_name, sizeof(output_name),
                 "%s",
                 test_cases[i]);

        char *extension = strstr(output_name, ".in");

        if (extension != NULL) {
            strcpy(extension, ".out");
        }

        char expected_path[300];

        snprintf(expected_path, sizeof(expected_path),
                 "%s/%s",
                 problem_directory,
                 output_name);

        printf("\nTest Case %d: %s\n",
               i + 1,
               test_cases[i]);

        /* Run submitted program */

        int status = run_program(
            "./submissions/temp_solution",
            input_path,
            "test_cases/actual.out"
        );

        /* Runtime error */

if (status == -2) {
    printf("Result: TIME LIMIT EXCEEDED\n");
    time_limit_exceeded++;
    continue;
}

if (status != 0) {
printf("Time Limit      : %d\n", time_limit_exceeded);
    runtime_errors++;
    continue;
}

/* Compare outputs */

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
    wrong_answers++;
}
        free(test_cases[i]);
    }

    /* Remove temporary executable */

    remove("submissions/temp_solution");

    /* Final summary */

    printf("\n====================\n");
    printf("       SUMMARY\n");
    printf("====================\n");

    printf("Total Tests     : %d\n", test_count);
    printf("Accepted        : %d\n", passed);
    printf("Wrong Answers   : %d\n", wrong_answers);
    printf("Runtime Errors  : %d\n", runtime_errors);
    printf("Time Limit      : %d\n", time_limit_exceeded);
    printf("--------------------\n");

if (test_count > 0 && passed == test_count) {
    printf("Final Result    : ACCEPTED\n");
}
else if (time_limit_exceeded > 0) {
    printf("Final Result    : TIME LIMIT EXCEEDED\n");
}
else if (runtime_errors > 0) {
    printf("Final Result    : RUNTIME ERROR\n");
}
else {
    printf("Final Result    : WRONG ANSWER\n");
}
    return 0;
}
