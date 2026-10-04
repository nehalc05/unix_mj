#include <stdio.h>
#include <string.h>
#include "judge.h"

int compare_output(const char *actual_file,
                   const char *expected_file) {

    FILE *actual = fopen(actual_file, "r");
    FILE *expected = fopen(expected_file, "r");

    if (actual == NULL || expected == NULL) {
        printf("Error opening output files.\n");

        if (actual != NULL)
            fclose(actual);

        if (expected != NULL)
            fclose(expected);

        return 0;
    }

    char actual_line[1000];
    char expected_line[1000];

    while (1) {

        char *a = fgets(actual_line, sizeof(actual_line), actual);
        char *e = fgets(expected_line, sizeof(expected_line), expected);

        if (a == NULL && e == NULL) {
            break;
        }

        if (a == NULL || e == NULL) {
            fclose(actual);
            fclose(expected);
            return 0;
        }

        if (strcmp(actual_line, expected_line) != 0) {
            fclose(actual);
            fclose(expected);
            return 0;
        }
    }

    fclose(actual);
    fclose(expected);

    return 1;
}

