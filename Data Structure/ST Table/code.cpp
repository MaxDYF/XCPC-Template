namespace RMQ
{
	vector< vector<int> > _data;
	vector<int> lg2;
	int func(int x, int y)
	{
		return max(x, y);
	}
	void init(vector<int> a)
	{
		int n = a.size();
		lg2 = vector<int>(n + 1);
		lg2[1] = 0;
		for (int i = 2; i <= n; i++)
			lg2[i] = lg2[i >> 1] + 1;
		_data = vector<vector<int> > (n, vector<int>(lg2[n] + 1));
		for (int i = 0; i < n; i++)
			_data[i][0] = a[i];
		for (int bit = 1; bit <= lg2[n]; bit++)
			for (int i = 0; i + (1 << bit) - 1 < n; i++)
				_data[i][bit] = func(_data[i][bit - 1], _data[i + (1 << (bit - 1))][bit - 1]);
	}
	int query(int l, int r)
	{
		int bit = lg2[r - l + 1];
		return func(_data[l][bit], _data[r - (1 << bit) + 1][bit]);
	}
}