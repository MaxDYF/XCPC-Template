#include <cstdint>
/*
 * 线段树模板
 * 默认为区间加法
 * 注意：默认下标从0开始，范围[0, n)
 */
template <class T> struct SegmentTree {
    struct Node {
        T val, lazy;
        int l, r;
    };
    vector<Node> tr;
    void updata(int p) { tr[p].val = tr[p << 1].val + tr[p << 1 | 1].val; }
    void build(int l, int r, vector<T> &a, int p = 1) {
        if (l == r) {
            tr[p].l = tr[p].r = l;
            tr[p].val = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, a, p << 1);
        build(mid + 1, r, a, p << 1 | 1);
        tr[p].l = l, tr[p].r = r;
        updata(p);
    }
    SegmentTree(int n) {
        tr.clear();
        tr.resize(n * 4);
        build(0, n - 1, vector<T>(n));
    }
    SegmentTree(vector<T> &a) {
        int n = a.size();
        tr.clear();
        tr.resize(n * 4);
        build(0, n - 1, a);
    }

    void spread(int p) {
        if (tr[p].lazy) {
            T t = tr[p].lazy;
            tr[p << 1].val += t * (tr[p << 1].r - tr[p << 1].l + 1), tr[p << 1].lazy += t;
            tr[p << 1 | 1].val += t * (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1), tr[p << 1 | 1].lazy += t;
            tr[p].lazy = 0;
        }
    }
    T query(int l, int r, int p = 1) {
        if (l <= tr[p].l && tr[p].r <= r)
            return tr[p].val;
        int mid = (tr[p].l + tr[p].r) >> 1;
        T sum = 0;
        spread(p);
        if (l <= mid)
            sum += query(l, r, p << 1);
        if (mid < r)
            sum += query(l, r, p << 1 | 1);
        return sum;
    }
    void add(int l, int r, int val, int p = 1) {
        if (l <= tr[p].l && tr[p].r <= r) {
            tr[p].val += (tr[p].r - tr[p].l + 1) * val;
            tr[p].lazy += val;
            return;
        }
        spread(p);
        int mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid)
            add(l, r, val, p << 1);
        if (mid < r)
            add(l, r, val, p << 1 | 1);
        updata(p);
    }
};