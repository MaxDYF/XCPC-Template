#include <bits/stdc++.h>

const int32_t N = 2e5 + 10;
const int64_t mod = 1e9 + 7;
int64_t fac[N], facRev[N];
auto quickPow(int64_t base, int32_t k)
{
    int64_t ans = 1LL;
    while (k)
    {
        if (k & 1)
            ans = (ans * base) % mod;
        base = (base * base) % mod;
        k >>= 1;
    }
    return ans;
}
void init()
{
    fac[0] = facRev[0] = 1;
    for (int64_t i = 1; i < N; i++)
        fac[i] = fac[i - 1] * i % mod;
    for (int64_t i = 1; i < N; i++)
        facRev[i] = quickPow(fac[i], mod - 2);
}
int64_t C(int n, int m)
{
    return fac[n] * facRev[m] % mod * facRev[n - m] % mod;
}