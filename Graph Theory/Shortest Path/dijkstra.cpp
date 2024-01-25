
const int N = 2e5 + 10;

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ll, int> pli;

namespace Graph
{
	vector<pli> to[N];
	void add(int x, int y, ll val)
	{
		to[x].push_back({val, y});
	}
	bool vis[N];
	ll   dis[N];
	void shortest_path(int from)
	{
		// using Dijkstra
		priority_queue<pli, vector<pli>, greater<pli> > q;
		q.push(make_pair(0, from));
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
					q.push(make_pair(dis[y], y));
				}
		}
	}
}
