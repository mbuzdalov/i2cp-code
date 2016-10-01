#include <cstdlib>

#include <algorithm>
#include <limits>
#include <iostream>
#include <utility>

using std::atoi;
using std::cout;
using std::endl;
using std::sort;

const int ITERATION_LIMIT = 10000;

struct bin_search_result {
    double interval_l;
    double interval_r;
    int iterations;

    bin_search_result(double interval_l, double interval_r, int iterations)
        : interval_l(interval_l)
        , interval_r(interval_r)
        , iterations(iterations) {}
};

bin_search_result bin_search(double (*f)(double), double l, double r) {
    double vMin = f(l), vMax = f(r);
    if (vMin > 0) return bin_search_result(l - 1, l, 0);
    if (vMax < 0) return bin_search_result(r, r + 1, 0);
    if (vMin == 0) return bin_search_result(l, l, 0);
    if (vMax == 0) return bin_search_result(r, r, 0);
    for (int iter = 1; ; ++iter) {
        if (iter > ITERATION_LIMIT) {
            return bin_search_result(l, r, iter);
        }
        double m = (l + r) / 2;
        if (l == m || r == m) return bin_search_result(l, r, iter);
        double v = f(m);
        if (v == 0) return bin_search_result(m, m, iter);
        if (v < 0) l = m; else r = m;
    }
}

bin_search_result bin_search_eps(double (*f)(double), double l, double r) {
    const double epsilon = 1e-9;
    int iter = 0;
    while (r - l > epsilon) {
        ++iter;
        if (iter > ITERATION_LIMIT) {
            return bin_search_result(l, r, iter);
        }
        double m = (l + r) / 2;
        if (f(m) < 0) l = m; else r = m;
    }
    return bin_search_result(l, r, iter);
}

bin_search_result bin_search_iter(double (*f)(double), double l, double r, int limit) {
    for (int iter = 0; iter < limit; ++iter) {
        double m = (l + r) / 2;
        if (f(m) < 0) l = m; else r = m;
    }
    return bin_search_result(l, r, limit);
}


double fun_1(double x) {
    return x;
}

double fun_2(double x) {
    return x + 412349128419.77615;
}

double fun_3(double x) {
    return atan(x) + x + 17;
}

double (*funs[])(double) = { &fun_1, &fun_2, &fun_3 };
char const *fun_names[] = { "x", "x + 412349128419.77615", "atan(x) + x + 17" };

void print(int index, bin_search_result const &r) {
    cout << "  Function " << fun_names[index] << ": ";
    if (r.iterations <= ITERATION_LIMIT) {
        cout << r.iterations << " iterations" << endl;
    } else {
        cout << "FAILED TO CONVERGE" << endl;
    }
    cout << "    f" << index << "(" << r.interval_l << ") = " << funs[index](r.interval_l) << endl;
    cout << "    f" << index << "(" << r.interval_r << ") = " << funs[index](r.interval_r) << endl;
}

int main() {
    cout.precision(std::numeric_limits<double>::max_digits10);

    double lower = -1e12;
    double upper = 1e11;

    cout << "Binary search with exact termination" << endl;
    for (int i = 0; i < 3; ++i) {
        print(i, bin_search(funs[i], lower, upper));
    }
    cout << "Binary search with epsilon" << endl;
    for (int i = 0; i < 3; ++i) {
        print(i, bin_search_eps(funs[i], lower, upper));
    }
    cout << "Binary search with iteration limit 50" << endl;
    for (int i = 0; i < 3; ++i) {
        print(i, bin_search_iter(funs[i], lower, upper, 50));
    }
    cout << "Binary search with iteration limit 70" << endl;
    for (int i = 0; i < 3; ++i) {
        print(i, bin_search_iter(funs[i], lower, upper, 70));
    }

    return 0;
}
