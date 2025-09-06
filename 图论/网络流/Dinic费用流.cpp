#include <bits/stdc++.h>
namespace Dinic {
using T = int64_t;
const int NODE = 1e5 + 10;
const int EDGE = 1e5 + 10;
struct Edge {
    int to, nxt;
    T flow, cost;
    // flow剩余流量
    // cost通过费用
} edge[EDGE];
int head[NODE];      // 邻接表头
int cnt = 1;         // 总边数
int pre[NODE];       // 表示当前增广路中每个节点的上一个节点
T flow[NODE];        // 到达当前节点的总流量
T cost[NODE];        // 到达当前节点的总花费
int last[NODE];      // 到达上一节点的边的编号
std::queue<int> que; // SPFA用队列
bool vis[NODE];      // 当前节点是否走过
int start, end;
void add(int x, int y, T flow, T cost) {
    edge[++cnt] = Edge{y, head[x], flow, cost};
    head[x] = cnt;
    edge[++cnt] = Edge{x, head[y], 0, -cost};
    head[y] = cnt;
}
bool spfa() {
    memset(flow, 0x3f, sizeof flow);
    memset(cost, 0x3f, sizeof cost);
    memset(vis, 0, sizeof vis);
    que.push(start);
    pre[end] = -1;
    cost[start] = 0;
    vis[start] = 1;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = edge[i].nxt) {
            int y = edge[i].to;
            if (edge[i].flow > 0 && cost[y] > cost[x] + edge[i].cost) {
                flow[y] = std::min(flow[x], edge[i].flow);
                cost[y] = cost[x] + edge[i].cost;
                last[y] = i;
                pre[y] = x;
                if (!vis[y]) {
                    vis[y] = 1;
                    que.push(y);
                }
            }
        }
    }
    return pre[end] != -1;
}
std::pair<T, T> work() {
    int maxflow = 0, mincost = 0;
    while (spfa()) {
        maxflow += flow[end];
        mincost += cost[end] * flow[end];
        int now = end;
        while (now != start) {
            edge[last[now]].flow -= flow[end];
            edge[last[now] ^ 1].flow += flow[end];
            now = pre[now];
        }
    }
    return {maxflow, mincost};
}
} // namespace Dinic
