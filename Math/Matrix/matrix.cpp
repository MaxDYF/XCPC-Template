//#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int inf = 1 << 30;
const long long llinf = 1ll << 60;
const double PI = acos(-1);

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;


template<class T, T MOD = 0>
class Matrix
{
private:

	int R, C;
	vector<vector<T> > a;
public:
	Matrix(){}
	Matrix(const int Rt, const int Ct, T init_val = 0)
	{
		a = vector<vector<T> >(Rt, vector<T>(Ct, init_val));
		R = Rt;
		C = Ct;
	}
	Matrix(vector<vector<T> > b)
	{
		a = b;
		R = a.size();
		C = a[0].size();
	}
	Matrix<T, MOD> operator * (const Matrix<T, MOD> b)
	{
		try
		{
			if (C != b.R)
				throw "SIZE DIFF";
		}
		catch(string code)
		{
			cout << "MATRIX ERROR @ OPERATOR * : " + code << endl;
			exit(0);
		}
		Matrix<T, MOD> c(R, b.C, 0);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < b.C; j++)
				for (int k = 0; k < C; k++)
				{
					if (MOD != 0)
						c.a[i][j] = (c.a[i][j] + (a[i][k] * b.a[k][j]) % MOD) % MOD;
					else
						c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]);
				}
		return c;
	}
	Matrix<T, MOD> operator + (const Matrix<T, MOD> b)
	{
		try
		{
			if (R != b.R || C != b.C)
				throw "SIZE DIFF";
		}
		catch(string code)
		{
			cout << "MATRIX ERROR @ OPERATOR + : " + code << endl;
			exit(0);
		}
		Matrix<T, MOD> c(R, C, 0);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (MOD != 0)
					c.a[i][j] = (a[i][j] + b.a[i][j]) % MOD;
				else
					c.a[i][j] = (a[i][j] + b.a[i][j]);
				
		return c;
	}
	Matrix<T, MOD> operator * (const T val)
	{
		Matrix<T, MOD> c(a);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (MOD != 0)
					c.a[i][j] = (c.a[i][j] * val) % MOD;
				else
					c.a[i][j] = (c.a[i][j] * val);
		return c;
	}
	Matrix<T, MOD> operator % (const T val)
	{
		Matrix<T, MOD> c(a);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				c.a[i][j] %= val;
		return c;
	}
	T sum()
	{
		T ans = 0;
		for (auto line : a)
			for (auto x : line)
				ans = (ans + x) % MOD;
		return ans;
	}
	void print()
	{
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				cout << a[i][j] << " \n"[j == C - 1];
	}
};
const ll mod = 1e9 + 7;
template<typename T>
T quickPow(T base, ll times, T initVal = 1)
{
	T ans = initVal;
	while (times)
	{
		if (times & 1)
			ans = ans * base % mod;
		base = base * base % mod;
		times >>= 1;
		
	}
	return ans;
}
void work()
{
	ll n, k;
	cin >> n >> k;
	vector<vector<ll> > a(n, vector<ll>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	Matrix<ll, mod> bs(a);
	if (k == 0)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cout << (int)(i == j) << " \n"[j == n];
	}
	else
		quickPow(bs, k - 1, bs).print();
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	work();
}