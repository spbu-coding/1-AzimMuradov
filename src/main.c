/*
 * Task 1
 *
 * Azim Muradov, group #171
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "integration_lib.h"

int read_interval(struct interval_t *interval);

char **run_experiments(struct interval_t interval, const int *steps_numbers, size_t experiments_number);

void free_string_array(char **array, size_t array_length);


int read_interval(struct interval_t *interval) {
    do {
        if (printf("Enter an interval \"a b\", where a >= 0 and b <= Pi, e.g. \"1 3\": ") < 0) {
            fprintf(stderr, "Cannot write to stdout\n");
            return -1;
        }

        if (scanf("%lf %lf", &interval->left_border, &interval->right_border) != 2) {
            fprintf(stderr, "Cannot read the interval\n");
            return -1;
        }


        if (interval->left_border < 0) {
            fprintf(stderr, "The left border of the interval must be greater than or equal to 0\n");
            continue;
        }

        if (interval->right_border > M_PI) {
            fprintf(stderr, "The right border of the interval must be less than or equal to Pi\n");
            continue;
        }

        if (interval->left_border >= interval->right_border) {
            fprintf(stderr, "The right border of the interval must be greater than the left\n");
            continue;
        }

        break;
    } while (true);

    return 0;
}

char **run_experiments(struct interval_t interval, const int *steps_numbers, size_t experiments_number) {
    char **results = malloc(experiments_number * sizeof *results);
    if (results == NULL) {
        return NULL;
    }

    int steps_number;
    double r_integral, s_integral;
    for (size_t i = 0; i < experiments_number; ++i) {
        steps_number = steps_numbers[i];
        r_integral = riemann_integration(sin, interval, steps_number);
        s_integral = simpson_integration(sin, interval, steps_number);

        results[i] = malloc(30 * sizeof(char));

        if (results[i] == NULL) {
            free_string_array(results, i);
            fprintf(stderr, "Cannot allocate memory for result string in %ld experiment\n", i);
            return NULL;
        }

        if (sprintf(results[i], "%d %.5f %.5f", steps_number, r_integral, s_integral) < 0) {
            free_string_array(results, i + 1);
            fprintf(stderr, "Cannot write result to string in %ld experiment\n", i);
            return NULL;
        }
    }

    return results;
}

void free_string_array(char **array, size_t array_length) {
    for (size_t i = 0; i < array_length; ++i) free(array[i]);
    free(array);
}


int main() {
    // Read input
    struct interval_t interval;
    if (read_interval(&interval)) {
        exit(EXIT_FAILURE);
    }

    int steps_numbers[] = {6, 10, 20, 100, 500, 1000};
    size_t experiments_number = sizeof(steps_numbers) / sizeof(steps_numbers[0]);

    // Run experiments and get they're result
    char **experiments_result = run_experiments(interval, steps_numbers, experiments_number);
    if (experiments_result == NULL) {
        exit(EXIT_FAILURE);
    }

    printf("Experiments' result:\n");
    for (size_t i = 0; i < experiments_number; ++i) {
        if (printf("%s\n", experiments_result[i]) < 0) {
            fprintf(stderr, "Cannot write %lu result to stdout\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // Free memory
    free_string_array(experiments_result, experiments_number);


    exit(EXIT_SUCCESS);
}
