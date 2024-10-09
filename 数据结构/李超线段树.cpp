/*
 * 李超线段树模板
 * 要求参数均为整数
 */
typedef long long i64;
template <int LEN>
class Lichao_SegmentTree
{
public:
    const i64 inf = 0x3f3f3f3f3f3f3f3f;
    struct Line
    {
        i64 k, b;
        Line(i64 _k = 0, i64 _b = 0) : k(_k), b(_b) {}
        i64 at(i64 x) const { return k * x + b; }
    };
    static bool less(const Line &x, const Line &y, const i64 &p)
    {
        return x.at(p) < y.at(p);
    }
    static double intersect(const Line &x, const Line &y)
    {
        return double(y.b - x.b) / double(y.k - x.k);
    }

    void init(int x1, int x2)
    {
        if (x1 > x2)
            minx = x2, maxx = x1;
        else
            minx = x1, maxx = x2;
        build(1, minx, maxx);
    }
    void insert(const Line &g, int x1, int x2) { _insert(g, x1, x2, 1, minx, maxx); }
    i64 ask(int x) const { return _getmax(x, 1, minx, maxx); }

private:
    struct Node
    {
        bool vis, has_line;
        Line f;
        Node() {}
        Node(bool _v, bool _h) : vis(_v), has_line(_h), f() {}
    };
    Node tr[LEN << 2];
    int minx, maxx;
    void build(int p, int l, int r)
    {
        tr[p] = Node(false, false);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void _update(Line g, int p, int l, int r)
    {
        tr[p].vis = true;
        if (!tr[p].has_line)
        {
            tr[p].has_line = true;
            tr[p].f = g;
            return;
        }
        Line &f = tr[p].f;
        int mid = (l + r) >> 1;
        if (less(f, g, mid))
            std::swap(f, g);
        if (l == r)
            return;
        if (less(f, g, l))
            _update(g, p << 1, l, mid);
        if (less(f, g, r))
            _update(g, p << 1 | 1, mid + 1, r);
    }
    void _insert(const Line &g, int x, int y, int p, int l, int r)
    {
        tr[p].vis = true;
        if (x <= l && r <= y)
            return _update(g, p, l, r);
        int mid = (l + r) >> 1;
        if (x <= mid)
            _insert(g, x, y, p << 1, l, mid);
        if (y > mid)
            _insert(g, x, y, p << 1 | 1, mid + 1, r);
    }
    i64 _getmax(int x, int p, int l, int r) const
    {
        if (!tr[p].vis)
            return -inf;
        i64 ans = tr[p].has_line ? tr[p].f.at(x) : -inf;
        if (l == r)
            return ans;
        int mid = (l + r) >> 1;
        if (x <= mid)
            return std::max(ans, _getmax(x, p << 1, l, mid));
        else
            return std::max(ans, _getmax(x, p << 1 | 1, mid + 1, r));
        return ans;
    }
};