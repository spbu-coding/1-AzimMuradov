/*
 * Task 1
 *
 * Azim Muradov, group #171
 */

#include "integration_lib.h"

double riemann_integration(function_d1_t f, struct interval_t interval, int steps_number) {
    const double delta = (interval.right_border - interval.left_border) / steps_number;

    double sum = 0.0;
    double x = interval.left_border;

    // f((x[0] + x[1]) / 2) + f((x[1] + x[2]) / 2) + ... + f((x[steps_number - 1] + x[steps_number]) / 2)
    for (int i = 0; i < steps_number; ++i) {
        sum += f(x + delta / 2);
        x += delta;
    }

    sum *= delta;

    return sum;
}

double simpson_integration(function_d1_t f, struct interval_t interval, int steps_number) {
    const double delta = (interval.right_border - interval.left_border) / steps_number;

    // 1/3 * f(x[0]) + 1/3 * f(x[steps_number])
    double sum = f(interval.left_border) / 3.0 + f(interval.right_border) / 3.0;
    double x = interval.left_border;

    // 4/3 * f(x[1]) + 2/3 * f(x[2]) + ... + 2/3 * f(x[steps_number-2]) + 4/3 * f(x[steps_number-1])
    for (int i = 1; i < steps_number - 2; i += 2) {
        x += delta;
        sum += 4.0 / 3.0 * f(x);
        x += delta;
        sum += 2.0 / 3.0 * f(x);
    }
    sum += 4.0 / 3.0 * f(x + delta);

    sum *= delta;

    return sum;
}
