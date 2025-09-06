// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int inf = 1 << 30;
const long long llinf = 1ll << 60;
const double PI = acos(-1);

#define lowbit(x) (x & -x)
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ll, int> pli;

long long n, m, k, q, x;

/*
 * Z函数模板
 * 实现了基础的Z函数功能
 * 注意，根据定义，z[0]=0，而非z[0]=n
 * 通过例题: https://www.luogu.com.cn/problem/P10320?contestId=156706
 */

namespace Zfunc {
vector<int> getZ(string s) {
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        // 如果不超出范围，则直接继承
        if (i <= r && i + z[i - l] - 1 < r)
            z[i] = z[i - l];
        // 否则，就尝试从r-l+1长度开始暴力扩展
        else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[i + z[i]] == s[z[i]])
                ++z[i];
        }
        // 更新l, r的边界
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
} // namespace Zfunc
void work() {
    string a, b;
    cin >> a >> b;
    int n = a.length(), m = b.length();
    string c = b + '*' + a;
    auto z1 = Zfunc::getZ(b), z2 = Zfunc::getZ(c);
    z1[0] = m;
    long long ans1 = 0, ans2 = 0;
    for (int i = 0; i < m; i++)
        ans1 ^= (ll)(i + 1) * (ll)(z1[i] + 1);
    for (int i = m + 1; i < n + m + 1; i++)
        ans2 ^= (ll)(i - m) * (ll)(z2[i] + 1);
    cout << ans1 << endl << ans2 << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    work();
}