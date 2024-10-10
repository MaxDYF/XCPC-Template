namespace NTT
{
    typedef long long i64;

    /// quick power
    /// @brief
    /// @tparam MOD
    /// @param x
    /// @param y
    /// @return
    template <i64 MOD>
    i64 qpow(i64 x, i64 y)
    {
        i64 ans = 1;
        while (y)
        {
            if (y & 1)
                ans = ans * x % MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return ans;
    }

    // make reversed binary representation array
    /// @brief
    /// @param rev
    /// @param len
    void makerev(std::vector<int> &rev, const int &len)
    {
        rev.resize(len);
        rev[0] = 0;
        rev[1] = len >> 1;
        int l = 0;
        while ((1 << l) < len)
            l++;
        for (int i = 2; i < len; ++i)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
        /*
            rev[i >> 1] is the reversed representation of i >> 1
            (i >> 1) << 1 = i, so in reversed representation we need rev[i >> 1] >> 1
            if i & 1 == 1, then the MSB of reversed representation should be 1
            that is (i & 1) << (l - 1)
        */
    }

    // iterative NTT
    /// @brief
    /// @tparam MOD
    /// @param A
    /// @param flag
    template <i64 MOD>
    void NTT(std::vector<i64> &A, const int &flag = 1)
    {
        static std::vector<int> rev;
        static const i64 prt = 3, invprt = qpow<MOD>(prt, MOD - 2);
        int n = A.size();
        if (int(rev.size()) != n)
            makerev(rev, n);
        for (int i = 0; i < n; ++i)
            if (rev[i] > i)
                std::swap(A[i], A[rev[i]]);
        for (int len = 2, m = 1; len <= n; m = len, len <<= 1)
        {
            i64 w1 = qpow<MOD>(flag == 1 ? prt : invprt, (MOD - 1) / len), wk;
            for (int l = 0, r = len, k; r <= n; l += len, r += len)
            {
                for (k = l, wk = 1; k < l + m; wk = wk * w1 % MOD, ++k)
                {
                    i64 x = A[k], y = A[k + m] * wk % MOD;
                    A[k] = (x + y) % MOD;
                    A[k + m] = (x - y + MOD) % MOD;
                }
            }
        }
    }
}