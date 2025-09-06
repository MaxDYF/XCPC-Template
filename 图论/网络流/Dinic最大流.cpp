#include <bits/stdc++.h>
namespace Dinic {

using T = int32_t;
// 定义储存流量的类型，默认为int32_t
const int CNT_NODE = 2e5 + 10;
// 定义节点Node的数量
const int CNT_EDGE = 2e5 + 10;
// 定义边的数量
struct Edge {
    int to;
    int nxt;
    T flow;
} e[CNT_EDGE];
int head[CNT_NODE], cnt = 1;
int n;
void add(int x, int y, T flow) {
    e[++cnt] = Edge{y, head[x], flow};
    head[x] = cnt;
    e[++cnt] = Edge{x, head[y], 0};
    head[y] = cnt;
    n = std::max(n, x);
    n = std::max(n, y);
}
int st, ed;
T dis[CNT_NODE];
int cur[CNT_NODE];
bool bfs() {
    std::queue<int> que;
    que.push(ed);
    memset(dis, 0, sizeof(dis));
    dis[ed] = 1;
    while (!que.empty()) {
        auto x = que.front();
        que.pop();
        cur[x] = head[x];
        for (auto i = head[x]; i; i = e[i].nxt) {
            auto y = e[i].to;
            if (!dis[y] && e[i ^ 1].flow) {
                dis[y] = dis[x] + 1;
                que.push(y);
            }
        }
    }
    return dis[st];
}
T dfs(int x, T flow) {
    auto rest = flow;
    if (!flow || x == ed)
        return flow;
    for (auto &i = cur[x]; i && rest; i = e[i].nxt) {
        auto y = e[i].to;
        if (dis[y] == dis[x] - 1 && e[i].flow) {
            auto k = dfs(y, std::min(rest, e[i].flow));
            e[i].flow -= k;
            e[i ^ 1].flow += k;
            rest -= k;
        }
    }
    return flow - rest;
}
T dinic() {
    for (int i = 1; i <= n; i++)
        cur[i] = head[i];
    T ans = 0, k;
    while (bfs())
        while (k = dfs(st, 0x3f3f3f3f))
            ans += k;
    return ans;
}
} // namespace Dinic