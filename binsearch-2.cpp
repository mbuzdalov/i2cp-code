#include <cstdlib>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>

using std::atoi;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::sort;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

using std::srand;
using std::rand;

pair<int, int> bin_search(int *a, int size, int what) {
    int l = 0, r = size - 1, vMin = a[l], vMax = a[r];
    if (vMin > what) return make_pair(-1, l);
    if (vMax < what) return make_pair(r, size);
    if (vMin == what) return make_pair(l, l);
    if (vMax == what) return make_pair(r, r);
    while (true) {
        int m = l + (r - l) / 2;
        if (l == m || r == m) return make_pair(l, r);
        int v = a[m];
        if (v == what) return make_pair(m, m);
        if (v < what) l = m; else r = m;
    }
}

#define assert(T) assert_impl((T), #T)

void assert_impl(bool expression, char const *expr) {
    if (!expression) {
        cout << " Error checking expression " << expr << endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Give a size" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int *a = new int[n];

    cout << "Generating array...";
    cout.flush();

    srand(239);
    for (int i = 0; i < n; ++i) {
        a[i] = rand();
    }
    cout << " done!" << endl;
    cout << "Sorting array...";
    cout.flush();
    sort(a, a + n);
    cout << " done!" << endl;

    milliseconds start_time_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    int nq = 10000000;

    cout << "Generating queries...";
    cout.flush();
    int *q = new int[nq];
    for (int t = 0; t < nq; ++t) {
        q[t] = rand();
    }
    cout << " done!" << endl;

    cout << "Doing " << nq << " binary searches...";
    cout.flush();
    for (int t = 0; t < nq; ++t) {
        int what = q[t];
        pair<int, int> rv = bin_search(a, n, what);
        if (rv.first == rv.second) {
            assert(0 <= rv.first && rv.first < n);
            assert(a[rv.first] == what);
        } else {
            if (rv.first == -1) {
                assert(rv.second == 0);
                assert(what < a[0]);
            } else if (rv.second == n) {
                assert(rv.first == n - 1);
                assert(what > a[n - 1]);
            } else {
                assert(rv.first + 1 == rv.second);
                assert(a[rv.first] < what && what < a[rv.second]);
            }
        }
    }
    cout << " done!" << endl;

    milliseconds finish_time_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    cout << "Time: " << (finish_time_ms - start_time_ms).count() << endl;

    return 0;
}
