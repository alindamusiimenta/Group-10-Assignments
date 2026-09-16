/*
 * Group 10 — Rolling Operations
 * Function: exponential_moving_average(data, alpha)
 *
 * EMA_t = alpha * x_t + (1 - alpha) * EMA_(t-1)
 * alpha is in (0, 1]. If you have a "span" instead (e.g. a 3-period EMA),
 * convert it first with: alpha = 2.0 / (span + 1).
 * First value has no history, so EMA_0 = x_0 (common convention).
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::vector;

vector<double> exponential_moving_average(const vector<double>& data, double alpha) {
    vector<double> result(data.size());
    if (data.empty()) return result;

    double ema_prev = data[0];
    result[0] = ema_prev;
    for (size_t i = 1; i < data.size(); ++i) {
        double ema_curr = alpha * data[i] + (1 - alpha) * ema_prev;
        result[i] = ema_curr;
        ema_prev = ema_curr;
    }
    return result;
}

void print_row(const std::string& label, const vector<double>& v, int precision = 3) {
    std::cout << std::left << std::setw(24) << label << "[ ";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << std::fixed << std::setprecision(precision) << v[i];
        if (i != v.size() - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

int main() {
    vector<double> column = {10, 12, 9, 15, 20, 18, 22, 25, 19, 30};
    double span = 3.0;
    double alpha = 2.0 / (span + 1);

    print_row("Data:", column, 0);
    print_row("exponential_moving_avg:", exponential_moving_average(column, alpha));

    return 0;
}
