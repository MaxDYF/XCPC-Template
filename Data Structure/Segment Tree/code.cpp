
const int N = 2e5 + 10;
#define lowbit(x) (x&-x)
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ll, int> pli;
namespace Segment
{
	typedef long long type;
	struct Node
	{
		type val, lazy;
		int l, r;
	};
	Node tr[N << 2];
	type a[N];
	void updata(int p)
	{
		tr[p].val = tr[p << 1].val + tr[p << 1 | 1].val;
	}
	void build(int l, int r, int p = 1)
	{
		if (l == r)
		{
			tr[p].l = tr[p].r = l;
			tr[p].val = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, p << 1);
		build(mid + 1, r, p << 1 | 1);
		tr[p].l = l, tr[p].r = r;
		updata(p);
	}
	void spread(int p)
	{
		if (tr[p].lazy)
		{
			type t = tr[p].lazy;
			tr[p << 1].val += t * (tr[p << 1].r - tr[p << 1].l + 1), tr[p << 1].lazy += t;
			tr[p << 1 | 1].val += t * (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1), tr[p << 1 | 1].lazy += t;
			tr[p].lazy = 0;
		}
	}
	type query(int l, int r, int p = 1)
	{
		if (l <= tr[p].l && tr[p].r <= r)
			return tr[p].val;
		int mid = (tr[p].l + tr[p].r) >> 1;
		type sum = 0;
		spread(p);
		if (l <= mid)
			sum += query(l, r, p << 1);
		if (mid < r)
			sum += query(l, r, p << 1 | 1);
		return sum;
	}
	void add(int l, int r, int val, int p = 1)
	{
		if (l <= tr[p].l && tr[p].r <= r)
		{
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
}