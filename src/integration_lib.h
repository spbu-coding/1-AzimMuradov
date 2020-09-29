/*
 * Task 1
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_1_INTEGRATION_LIB_H
#define TASK_1_INTEGRATION_LIB_H

/**
 * Real interval [left_border, right_border]
 */
struct interval_t {
    double left_border;
    double right_border;
};

/**
 * f: A -> B, where A, B are subsets of R (real numbers)
 */
typedef double (*function_d1_t)(double);

/**
 * Midpoint rule
 *
 * For n steps (n + 1 points):
 * sum = f((x[0] + x[1]) / 2) + f((x[1] + x[2]) / 2) + ... + f((x[n - 1] + x[n]) / 2)
 */
double riemann_integration(function_d1_t f, struct interval_t interval, int steps_number);

/**
 * Composite Simpson's rule
 *
 * For n steps (n + 1 points):
 * sum = 1/3 * (f(x[0]) + 4 * f(x[1]) + 2 * f(x[2]) + ... + 2 * f(x[n-2]) + 4 * f(x[n-1]) + f(x[n]))
 */
double simpson_integration(function_d1_t f, struct interval_t interval, int steps_number);

#endif // TASK_1_INTEGRATION_LIB_H
