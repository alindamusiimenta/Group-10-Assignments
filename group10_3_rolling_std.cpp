/*
 * Group 10 — Rolling Operations
 * Function: rolling_std(data, window, ddof=1)
 *
 * Standard deviation of the last `window` values.
 * ddof = 1 -> sample std (Polars/Pandas default)
 * ddof = 0 -> population std
 * Positions before a full window is available hold NaN.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using std::vector;

const double NA = std::numeric_limits<double>::quiet_NaN();

vector<double> rolling_std(const vector<double>& data, int window, int ddof = 1) {
    vector<double> result(data.size(), NA);
    for (size_t i = 0; i < data.size(); ++i) {
        if (static_cast<int>(i) < window - 1) continue;

        double sum = 0.0;
        for (size_t j = i - window + 1; j <= i; ++j) sum += data[j];
        double mean = sum / window;

        double sq_diff_sum = 0.0;
        for (size_t j = i - window + 1; j <= i; ++j) {
            double diff = data[j] - mean;
            sq_diff_sum += diff * diff;
        }
        double variance = sq_diff_sum / (window - ddof);
        result[i] = std::sqrt(variance);
    }
    return result;
}

void print_row(const std::string& label, const vector<double>& v, int precision = 3) {
    std::cout << std::left << std::setw(20) << label << "[ ";
    for (size_t i = 0; i < v.size(); ++i) {
        if (std::isnan(v[i])) std::cout << "None";
        else std::cout << std::fixed << std::setprecision(precision) << v[i];
        if (i != v.size() - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

int main() {
    vector<double> column = {10, 12, 9, 15, 20, 18, 22, 25, 19, 30};
    int window = 3;

    print_row("Data:", column, 0);
    print_row("rolling_std(w=3):", rolling_std(column, window));

    return 0;
}
