#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
char a[N], b[N];
int p[N];
int main() {
    int n, m;
    cin >> (a + 1) >> (b + 1);
    n = strlen(a + 1);
    m = strlen(b + 1);
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && b[i] != b[j + 1])
            j = p[j];
        if (b[j + 1] == b[i])
            j++;
        p[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && a[i] != b[j + 1])
            j = p[j];
        if (a[i] == b[j + 1])
            j++;
        if (j == m) {
            cout << i - m + 1 << '\n';
            j = p[j];
        }
    }
    for (int i = 1; i <= m; i++)
        cout << p[i] << ' ';
}