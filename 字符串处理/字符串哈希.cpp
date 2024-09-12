// #pragma GCC optimize(2)
#include <bits/stdc++.h>

const int N = 2e5 + 10;
const int inf = 1 << 30;
const long long llinf = 1ll << 60;
const double PI = acos(-1);

#define lowbit(x) (x & -x)
/*
 *	字符串哈希模板
 *	使用namespace进行封装
 *	模板题为HDU1686
 *	Link: https://acm.hdu.edu.cn/showproblem.php?pid=1686
 */
typedef std::pair<int, int> HashPair;
const int CHAR_SIZE = 26; // 字符集大小
class Hash
{
private:
	std::vector<HashPair> hashPow;
	std::vector<HashPair> hashVal;
	const int mod1 = 100000007,
			  mod2 = 100000037;

	/*
	 *	字符转换函数
	 *	将字符转换为Hash中的编号
	 */
	int transChar(char ch)
	{
		return (ch - 'A' + 1);
	}
	/*
	 *	序列生成Hash生成函数并储存
	 */
	void makeHash(std::string &s)
	{
		size_t len = s.length();
		hashPow.clear();
		hashVal.clear();
		hashPow.resize(len);
		hashVal.resize(len);
		hashPow[0] = {1LL, 1LL};
		for (int i = 1; i < len; i++)
		{
			hashPow[i].first = (int64_t)hashPow[i - 1].first * (CHAR_SIZE + 1) % mod1;
			hashPow[i].second = (int64_t)hashPow[i - 1].second * (CHAR_SIZE + 1) % mod2;
		}
		for (size_t i = 0; i < len; i++)
		{
			hashVal[i].first = (i > 0) ? ((int64_t)hashVal[i - 1].first * (CHAR_SIZE + 1LL) + transChar(s[i])) % mod1
									   : transChar(s[i]) % mod1;
			hashVal[i].second = (i > 0) ? ((int64_t)hashVal[i - 1].second * (CHAR_SIZE + 1LL) + transChar(s[i])) % mod2
										: transChar(s[i]) % mod2;
		}
	}

public:
	Hash(std::string &str)
	{
		makeHash(str);
	}
	/*
	 *  截取某一段的Hash值
	 *	传入参数为[l, r)
	 *	即前闭后开形式
	 *  默认返回一个HashPair
	 */
	HashPair subHash(int l, int r)
	{
		if (l >= r)
			return {0, 0};
		if (l == 0)
			return hashVal[r - 1];
		else
		{
			HashPair result;
			result.first = ((int64_t)hashVal[r - 1].first -
							(int64_t)hashVal[l - 1].first * hashPow[r - l].first % mod1 + mod1) %
						   mod1;
			result.second = ((int64_t)hashVal[r - 1].second -
							 (int64_t)hashVal[l - 1].second * hashPow[r - l].second % mod2 + mod2) %
							mod2;
			return result;
		}
	}
};

int n, m, k, q;
void work()
{
	using namespace std;
	std::string w, t;
	cin >> w >> t;
	Hash word(w), passage(t);
	int len = w.length();
	int ans = 0;
	for (int i = len; i <= t.length(); i++)
		if (word.subHash(0, len) == passage.subHash(i - len, i))
			ans++;
	cout << ans << endl;
}
int main()
{

	using namespace std;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t-- > 0)
		work();
}