template <class T>
struct SegmentTree
{
    struct Node
    {
        T val, lazy;
        int l, r;
    };
    vector<Node> tr;
    void update(int p)
    {
        tr[p].val = (tr[p << 1].val + tr[p << 1 | 1].val);
    }
    void build(int l, int r, vector<T> &a, int p = 1)
    {

        tr[p].l = l;
        tr[p].r = r;
        tr[p].lazy = 0;
        if (l == r)
        {
            tr[p].val = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, a, p << 1);
        build(mid + 1, r, a, p << 1 | 1);
        update(p);
    }
    SegmentTree() {}
    SegmentTree(int n)
    {
        tr.resize(n * 4);
        vector<T> empty(n);
        build(0, n - 1, empty);
    }
    SegmentTree(vector<T> &a)
    {
        int n = a.size();
        tr.resize(n * 4);
        build(0, n - 1, a);
    }
    void pushdown(int p)
    {
        if (tr[p].lazy)
        {
            T t = tr[p].lazy;
            tr[p << 1].val += t * (tr[p << 1].r - tr[p << 1].l + 1);
            tr[p << 1].lazy += t;
            tr[p << 1 | 1].val += t * (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1);
            tr[p << 1 | 1].lazy += t;
            tr[p].lazy = 0;
        }
    }
    T query(int l, int r, int p = 1)
    {
        if (l <= tr[p].l && tr[p].r <= r)
            return tr[p].val;
        int mid = (tr[p].l + tr[p].r) >> 1;
        T sum = 0;
        pushdown(p);
        if (l <= mid)
            sum += query(l, r, p << 1);
        if (mid < r)
            sum += query(l, r, p << 1 | 1);
        return sum;
    }
    void add(int l, int r, int val, int p = 1)
    {
        if (l <= tr[p].l && tr[p].r <= r)
        {
            tr[p].val += (tr[p].r - tr[p].l + 1) * val;
            tr[p].lazy += val;
            return;
        }
        pushdown(p);
        int mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid)
            add(l, r, val, p << 1);
        if (mid < r)
            add(l, r, val, p << 1 | 1);
        update(p);
    }
};
template <class T>
struct ChainPartition
{
    vector<vector<int>> son;
    vector<int> dep, top, siz, hson, lnk2seg, lnk2tree, f;
    vector<T> segval, treeval;
    int dfnCount;
    SegmentTree<T> tr;
    ChainPartition() {}
    ChainPartition(int n)
    {
        dfnCount = 0;
        segval.resize(n);
        f.resize(n);
        dep.resize(n);
        top.resize(n);
        siz.resize(n);
        hson.resize(n);
        lnk2seg.resize(n);
        lnk2tree.resize(n);
        son.resize(n);
        tr = SegmentTree<T>(n);
    }
    ChainPartition(vector<T> a)
    {
        int n = a.size();
        dfnCount = 0;
        segval.resize(n);
        f.resize(n);
        dep.resize(n);
        top.resize(n);
        siz.resize(n);
        hson.resize(n);
        lnk2seg.resize(n);
        lnk2tree.resize(n);
        son.resize(n);
        treeval = a;
    }
    void addEdge(int x, int y)
    {
        son[x].push_back(y);
        son[y].push_back(x);
    }
    void dfs1(int x, int fa, int depth = 1)
    {
        dep[x] = depth;
        siz[x] = 1;
        hson[x] = -1;
        f[x] = fa;
        for (int y : son[x])
        {
            if (y == fa)
                continue;
            dfs1(y, x, depth + 1);
            siz[x] += siz[y];
            if (hson[x] == -1 || siz[hson[x]] < siz[y])
                hson[x] = y;
        }
    }
    void dfs2(int x, int nowtop)
    {
        top[x] = nowtop;
        lnk2seg[x] = dfnCount++;
        lnk2tree[lnk2seg[x]] = x;
        segval[lnk2seg[x]] = treeval[x];
        if (hson[x] == -1)
            return;
        dfs2(hson[x], nowtop);
        for (int y : son[x])
        {
            if (y == f[x] || y == hson[x])
                continue;
            dfs2(y, y);
        }
    }
    void init(int root = 0)
    {
        dfs1(root, -1);
        dfs2(root, root);
        tr = SegmentTree(segval);
    }
    T querySubtree(int x)
    {
        return tr.query(lnk2seg[x], lnk2seg[x] + siz[x] - 1);
    }
    void addSubtree(int x, T val)
    {
        tr.add(lnk2seg[x], lnk2seg[x] + siz[x] - 1, val);
    }
    int getLCA(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = f[top[x]];
        }
        if (dep[x] < dep[y])
            return x;
        else
            return y;
    }
    void add(int x, int y, T val)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            tr.add(lnk2seg[top[x]], lnk2seg[x], val);
            x = f[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        tr.add(lnk2seg[x], lnk2seg[y], val);
    }
    T query(int x, int y)
    {
        T ans = 0;
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            ans += tr.query(lnk2seg[top[x]], lnk2seg[x]);
            x = f[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        ans += tr.query(lnk2seg[x], lnk2seg[y]);
        return ans;
    }
};