#include <bits/stdc++.h>
/*
 * FHQ Treap模板(区间反转版)
 * 功能：区间反转
 * 基准模板：洛谷P3391 【模板】文艺平衡树
 * Link: https://www.luogu.com.cn/problem/P3391
 */
template <class T> class Tree {

  private:
    struct Node {
        /* data */
        size_t son[2];
        int32_t rand;
        size_t size;
        T val;
        bool tag;
    };
    int32_t seed;
    size_t root, cnt;
    std::vector<Node> tr;
    int32_t rand() { return seed = ((int64_t)(seed) * 238973) % 2147483647; }
    int32_t add(T val) {
        tr.push_back(Node{{0, 0}, rand(), 1, val, 0});
        return tr.size() - 1;
    }
    void spread(int32_t now) {
        if (!tr[now].tag)
            return;
        std::swap(tr[now].son[0], tr[now].son[1]);
        tr[tr[now].son[0]].tag ^= 1;
        tr[tr[now].son[1]].tag ^= 1;
        tr[now].tag = 0;
    }
    void updata(size_t now) { tr[now].size = tr[tr[now].son[0]].size + tr[tr[now].son[1]].size + 1; }
    void split(size_t now, size_t &a, size_t &b, size_t val) {
        if (!now) {
            a = b = 0;
            return;
        }
        spread(now);
        if (tr[tr[now].son[0]].size + 1 <= val) {
            a = now;
            split(tr[now].son[1], tr[now].son[1], b, val - tr[tr[now].son[0]].size - 1);
        } else {
            b = now;
            split(tr[now].son[0], a, tr[now].son[0], val);
        }
        updata(now);
    }
    int32_t merge(size_t a, size_t b) {
        if (!a || !b) {
            return a | b;
        }
        if (tr[a].rand < tr[b].rand) {
            spread(a);
            tr[a].son[1] = merge(tr[a].son[1], b);
            updata(a);
            return a;
        } else {
            spread(b);
            tr[b].son[0] = merge(a, tr[b].son[0]);
            updata(b);
            return b;
        }
    }
    void printF(size_t now) {
        spread(now);
        if (tr[now].son[0])
            printF(tr[now].son[0]);
        std::cout << tr[now].val << ' ';
        if (tr[now].son[1])
            printF(tr[now].son[1]);
    }

  public:
    Tree(int32_t initSeed = 19260917) { tr.push_back(Node{{0, 0}, rand(), 0, std::numeric_limits<T>::min(), 0}); };
    void get(std::vector<T> a) {
        for (auto x : a)
            root = merge(root, add(x));
    }
    void reverse(size_t l, size_t r) {
        size_t left, right, pos;
        split(root, left, right, r);
        split(left, left, pos, l - 1);
        tr[pos].tag ^= 1;
        root = merge(merge(left, pos), right);
    }

    void print() { printF(root); }
};
Tree<int32_t> a;
int32_t main() {
    int32_t n, m;
    std::cin >> n >> m;
    std::vector<int32_t> num(n);
    for (size_t i = 0; i < n; i++)
        num[i] = i + 1;
    a.get(num);
    for (size_t i = 1, l, r; i <= m; i++) {
        std::cin >> l >> r;
        a.reverse(l, r);
    }
    a.print();
}