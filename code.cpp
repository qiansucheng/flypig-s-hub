#include <iostream>
#include <cmath>
#include "limits.h"
#include <algorithm>
using namespace std;

class Sparse_Table {
private:
    int n, maxi;
    int *a, **st;

public:
    Sparse_Table(int *arr, int len) {
        n = len;
        maxi = (int) (log(n - 1));

        // just do usual allocation
        a = new int[n + 1];
        st = new int*[maxi + 1];
        for(int i = 0; i <= maxi; ++i)
            st[i] = new int[(n << 1) + 5];

        // assign array
        for(int i = 1; i <= n; ++i)
            a[i] = arr[i];
        for(int i = n + 1; i <= 2 * n; ++i)
            a[i] = INT_MIN;
        // pre-processing
        for(int j = 1; j <= 2 * n; ++j)
            st[0][j] = a[j];
        for(int i = 1; i <= maxi; ++i) {
            for(int j = 1; j <= n; ++j) {
                st[i][j] = max(st[i-1][j], st[i-1][j+(int)pow(2, i-1)]);
            }
        }
    }
    int query(int l, int r) {
        return max(st[(int)log(r-l)][l], st[(int)log(r-l)][r-(int)pow(2, (int)log(r-l))]);
    }
};

const int maxn = 1000;
int n, a[maxn];

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];

    Sparse_Table st(a, n);

    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; ++j) {
            printf("[%d,%d]: %d\n", i, j, st.query(i, j));
        }
    }
    return 0;
}
