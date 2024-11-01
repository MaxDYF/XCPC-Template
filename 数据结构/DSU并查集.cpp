struct DSU
{
    vector<int> f, siz;
    DSU() {}
    DSU(int n)
    {
        f.resize(n + 1);
        siz.resize(n + 1);
        for (int i = 1; i <= n; i++)
            f[i] = i, siz[i] = 1;
    }
    int find(int x)
    {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        f[x] = y;
        siz[y] += siz[x];
    }
};