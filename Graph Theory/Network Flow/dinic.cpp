#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    unsigned short to;
    unsigned nxt, flow;
} e[200002];
unsigned head[10001], cnt = 1;
void add(unsigned short x, unsigned short y, unsigned flow)
{
    e[++cnt] = Edge{y, head[x], flow};
    head[x] = cnt;
    e[++cnt] = Edge{x, head[y], 0};
    head[y] = cnt;
}
unsigned short S, T;
short dis[10001];
bool bfs()
{
    queue<unsigned> que;
    que.push(T);
    memset(dis, 0, sizeof dis);
    dis[T] = 1;
    while (!que.empty())
    {
        int x = que.front();
        que.pop();
        for (int i = head[x]; i; i = e[i].nxt)
        {
            unsigned short y = e[i].to;
            if (!dis[y] && e[i ^ 1].flow)
            {，，。
                dis[y] = dis[x] + 1;
                que.push(y);
            }
        }
    }
    return dis[S];
}
unsigned dfs(unsigned short x, unsigned flow)
{
    unsigned rest = flow;
    if (!flow || x == T)
        return flow;
    for (unsigned i = head[x]; i && rest; i = e[i].nxt)
    {
        unsigned short y = e[i].to;
        if (dis[y] == dis[x] - 1 && e[i].flow)
        {
            unsigned k = dfs(y, min(rest, e[i].flow));
            e[i].flow -= k;
            e[i ^ 1].flow += k;
            rest -= k;
        }
    }
    return flow - rest;
}
unsigned dinic()
{
    unsigned ans = 0, k;
    while (bfs())
        while (k = dfs(S, 0x3f3f3f3f))
            ans += k;
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    unsigned m, n;
    cin >> n >> m >> S >> T;
    for (unsigned i = 0; i < m; i++)
    {
        unsigned short x, y;
        unsigned z;
        cin >> x >> y >> z;
        add(x, y, z);
    }
    cout << dinic() << endl;
}