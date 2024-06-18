#include <bits/stdc++.h>
namespace Dinic
{

    using T = int64_t;
    // 定义储存流量的类型，默认为int32_t
    const size_t CNT_NODE = 2e5 + 10;
    // 定义节点Node的数量
    const size_t CNT_EDGE = 2e5 + 10;
    // 定义边的数量
    struct Edge
    {
        size_t to;
        size_t nxt;
        T flow;
    } e[CNT_EDGE];
    size_t head[CNT_NODE], cnt = 1;
    void add(size_t x, size_t y, T flow)
    {
        e[++cnt] = Edge{y, head[x], flow};
        head[x] = cnt;
        e[++cnt] = Edge{x, head[y], 0};
        head[y] = cnt;
    }
    size_t st, ed;
    T dis[CNT_NODE];
    bool bfs()
    {
        std::queue<size_t> que;
        que.push(ed);
        memset(dis, 0, sizeof dis);
        dis[ed] = 1;
        while (!que.empty())
        {
            auto x = que.front();
            que.pop();
            for (auto i = head[x]; i; i = e[i].nxt)
            {
                auto y = e[i].to;
                if (!dis[y] && e[i ^ 1].flow)
                {
                    dis[y] = dis[x] + 1;
                    que.push(y);
                }
            }
        }
        return dis[st];
    }
    T dfs(size_t x, T flow)
    {
        auto rest = flow;
        if (!flow || x == ed)
            return flow;
        for (auto i = head[x]; i && rest; i = e[i].nxt)
        {
            auto y = e[i].to;
            if (dis[y] == dis[x] - 1 && e[i].flow)
            {
                auto k = dfs(y, std::min(rest, e[i].flow));
                e[i].flow -= k;
                e[i ^ 1].flow += k;
                rest -= k;
            }
        }
        return flow - rest;
    }
    T dinic()
    {
        T ans = 0, k;
        while (bfs())
            while (k = dfs(st, 0x3f3f3f3f))
                ans += k;
        return ans;
    }
}
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    size_t m, n;
    std::cin >> n >> m >> Dinic::st >> Dinic::ed;
    for (size_t i = 0; i < m; i++)
    {
        size_t x, y;
        int32_t z;
        std::cin >> x >> y >> z;
        Dinic::add(x, y, z);
    }
    std::cout << Dinic::dinic() << std::endl;
}