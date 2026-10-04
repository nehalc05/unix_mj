#include <stdio.h>
#include "runner.h"

int main() {

    printf("UNIX Mini Judge\n");
    printf("----------------\n");

    printf("Running submission...\n");

    int status = run_program(
        "./submissions/solution",
        "test_cases/test1.in",
        "test_cases/actual.out"
    );

    if (status == 0) {
        printf("Submission executed successfully.\n");
    } else {
        printf("Submission failed.\n");
    }

    return 0;
}
