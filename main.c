#include <stdio.h>
#include "runner.h"
#include "judge.h"

int main() {

    printf("UNIX Mini Judge\n");
    printf("----------------\n");

    printf("Running submission...\n");

    int status = run_program(
        "./submissions/solution",
        "test_cases/test1.in",
        "test_cases/actual.out"
    );

    if (status != 0) {
        printf("Runtime Error\n");
        return 1;
    }

    printf("Submission executed successfully.\n");

    int result = compare_output(
        "test_cases/actual.out",
        "test_cases/test1.out"
    );

    if (result == 1) {
        printf("Result: ACCEPTED\n");
    } else {
        printf("Result: WRONG ANSWER\n");
    }

    return 0;
}
