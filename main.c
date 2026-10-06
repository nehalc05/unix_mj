#include <stdio.h>
#include <string.h>
#include "runner.h"
#include "judge.h"

int main() {

    int choice;

    printf("UNIX MINI JUDGE\n");
    printf("----------------\n");

    printf("Available Problems:\n");
    printf("1. Sum of Two Numbers\n");
    printf("2. Find Maximum\n");

    printf("\nEnter problem number: ");
    scanf("%d", &choice);

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

    printf("\nSelected Problem: %d\n", choice);
    printf("Running test cases...\n");

    const char *input_files[] = {
        "test1.in",
        "test2.in"
    };

    const char *expected_files[] = {
        "test1.out",
        "test2.out"
    };

    int total_tests = 2;
    int passed = 0;

    char input_path[200];
    char expected_path[200];

    for (int i = 0; i < total_tests; i++) {

        sprintf(input_path, "%s/%s",
                problem_directory, input_files[i]);

        sprintf(expected_path, "%s/%s",
                problem_directory, expected_files[i]);

        printf("\nTest Case %d:\n", i + 1);

        int status = run_program(
            "./submissions/solution",
            input_path,
            "test_cases/actual.out"
        );

        if (status != 0) {
            printf("Result: RUNTIME ERROR\n");
            continue;
        }

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

    printf("\n----------------\n");
    printf("Tests Passed: %d/%d\n", passed, total_tests);

    if (passed == total_tests) {
        printf("Final Result: ACCEPTED\n");
    }
    else {
        printf("Final Result: WRONG ANSWER\n");
    }

    return 0;
}
