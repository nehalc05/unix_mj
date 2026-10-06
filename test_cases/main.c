#include <stdio.h>
#include "runner.h"
#include "judge.h"

int main() {

    printf("UNIX Mini Judge\n");
    printf("----------------\n");

    const char *inputs[] = {
        "test_cases/test1.in",
        "test_cases/test2.in",
        "test_cases/test3.in"
    };

    const char *expected[] = {
        "test_cases/test1.out",
        "test_cases/test2.out",
        "test_cases/test3.out"
    };

    int total_tests = 3;
    int passed = 0;

    for (int i = 0; i < total_tests; i++) {

        printf("\nRunning Test Case %d...\n", i + 1);

        int status = run_program(
            "./submissions/solution",
            inputs[i],
            "test_cases/actual.out"
        );

        if (status != 0) {
            printf("Result: RUNTIME ERROR\n");
            continue;
        }

        int result = compare_output(
            "test_cases/actual.out",
            expected[i]
        );

        if (result == 1) {
            printf("Result: ACCEPTED\n");
            passed++;
        } else {
            printf("Result: WRONG ANSWER\n");
        }
    }

    printf("\n----------------\n");
    printf("Tests Passed: %d/%d\n", passed, total_tests);

    if (passed == total_tests) {
        printf("Final Result: ACCEPTED\n");
    } else {
        printf("Final Result: WRONG ANSWER\n");
    }

    return 0;
}
