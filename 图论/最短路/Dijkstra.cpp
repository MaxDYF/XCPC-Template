#include <bits/stdc++.h>
const int N = 2e5 + 10;

namespace Graph
{
    typedef int64_t T;
    typedef std::pair<int64_t, int32_t> pli;
    std::vector<pli> to[N];
    void add(int x, int y, T val)
    {
        to[x].push_back({val, y});
    }
    bool vis[N];
    T dis[N];
    void shortest_path(int32_t from)
    {
        // using Dijkstra
        std::priority_queue<pli, std::vector<pli>, std::greater<pli>> q;
        q.push(std::make_pair(0, from));
        memset(dis, 0x3f, sizeof dis);
        memset(vis, 0, sizeof vis);
        dis[from] = 0;
        while (!q.empty())
        {
            auto [nowval, x] = q.top();
            q.pop();
            if (vis[x])
                continue;
            vis[x] = 1;
            for (auto [val, y] : to[x])
                if (dis[y] > dis[x] + val)
                {
                    dis[y] = dis[x] + val;
                    q.push(std::make_pair(dis[y], y));
                }
        }
    }
}
