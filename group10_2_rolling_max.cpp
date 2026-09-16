/*
 * Group 10 — Rolling Operations
 * Function: rolling_max(data, window)
 *
 * Maximum of the last `window` values, sliding one step at a time.
 * Positions before a full window is available hold NaN, because
 * there isn't enough data yet to compute the statistic.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iomanip>

using std::vector;

const double NA = std::numeric_limits<double>::quiet_NaN();

vector<double> rolling_max(const vector<double>& data, int window) {
    vector<double> result(data.size(), NA);
    for (size_t i = 0; i < data.size(); ++i) {
        if (static_cast<int>(i) < window - 1) continue;
        double m = data[i - window + 1];
        for (size_t j = i - window + 2; j <= i; ++j)
            m = std::max(m, data[j]);
        result[i] = m;
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
    print_row("rolling_max(w=3):", rolling_max(column, window));

    return 0;
}
