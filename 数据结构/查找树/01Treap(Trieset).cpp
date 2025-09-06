
#include <bits/stdc++.h>
class Trieset {
  private:
    std::vector<std::array<int, 2>> tr;
    std::vector<int> siz;

  public:
    Trieset() {
        tr.resize(2);
        siz.resize(2);
        tr[0] = {};
        tr[1] = {};
    }
    void clear() { (*this) = Trieset(); }
    void insert(int x, int cnt = 1) {
        int now = 1;
        for (int i = 31, t; i >= 0; i--) {
            t = (x >> i) & 1;
            if (!tr[now][t]) {
                tr.push_back({});
                siz.push_back(0);
                tr[now][t] = tr.size() - 1;
            }
            siz[now = tr[now][t]] += cnt;
        }
    }
    bool erase(int x, int cnt = 1) {
        int now = 1;
        for (int i = 31, t; i >= 0; i--) {
            t = (x >> i) & 1;
            if (!tr[now][t])
                return 0;
            siz[now = tr[now][t]] -= cnt;
            if (siz[now] < 0)
                siz[now] = 0;
        }
        return 1;
    }
    int find_by_rank(int rank) {
        int ans = 0, now = 1;
        for (int i = 31; i >= 0; i--) {
            if (siz[tr[now][0]] < rank) {
                rank -= siz[tr[now][0]];
                ans |= 1 << i;
                now = tr[now][1];
            } else {
                now = tr[now][0];
            }
        }
        return ans;
    }
    int find_rank(int val) {
        int rank = 0, now = 1;
        for (int i = 31; i >= 0; i--) {
            int t = (val >> i) & 1;
            rank += t * (siz[tr[now][0]]);
            now = tr[now][t];
        }
        return rank + 1;
    }
    int prev(int val) { return find_by_rank(find_rank(val) - 1); }
    int next(int val) { return find_by_rank(find_rank(val + 1)); }
} a;