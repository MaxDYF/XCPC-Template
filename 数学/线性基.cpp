struct Basis
{
#define BITSIZ 63
    typedef unsigned long long ull;
    std::array<ull, BITSIZ> arr;
    int dim = 0;
    Basis()
    {
        fill(arr.begin(), arr.end(), 0);
        dim = 0;
    }
    void insert(ull x)
    {
        for (int i = BITSIZ - 1; i >= 0; i--)
            if ((x >> i) & 1ULL)
                if (arr[i])
                    x ^= arr[i];
                else
                {
                    arr[i] = x;
                    dim++;
                    break;
                }
    }
    void join(Basis b)
    {
        for (int i = 0; i < BITSIZ; i++)
            if (b.arr[i])
                insert(b.arr[i]);
    }
    ull calcMaxNum(ull base = 0)
    {
        for (int i = BITSIZ - 1; i >= 0; i--)
            if ((arr[i] ^ base) > base)
                base ^= arr[i];
        return base;
    }
    // 返回行最简矩阵
    Basis getSimplestForm()
    {
        Basis tmp = *this;
        for (int i = BITSIZ - 1; i >= 0; i--)
        {
            if (tmp.arr[i] == 0)
                continue;
            for (int j = i - 1; j >= 0; j--)
                if ((tmp.arr[i] >> j) & 1ULL)
                    if (tmp.arr[j])
                        tmp.arr[i] ^= tmp.arr[j];
        }
        return tmp;
    }
    ull getDimention()
    {
        return dim;
    }
    // 返回第k小的异或和,  必须是行最简矩阵
    ull calcKthNum(ull k)
    {
        if (k == 0)
            return 0;
        ull ans = 0;
        for (int i = 0; k && i < BITSIZ; i++)
            if (arr[i])
            {
                if (k & 1)
                    ans ^= arr[i];
                k >>= 1;
            }
        if (k)
            return -1;
        return ans;
    }
};