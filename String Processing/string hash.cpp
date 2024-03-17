//#pragma GCC optimize(2)
#include <bits/stdc++.h>

const int N = 2e5 + 10;
const int inf = 1 << 30;
const long long llinf = 1ll << 60;
const double PI = acos(-1);

#define lowbit(x) (x&-x)
/*
 *	字符串哈希模板
 *	使用namespace进行封装
 *	模板题为HDU1686
 *	Link: https://acm.hdu.edu.cn/showproblem.php?pid=1686
 */
namespace stringHash
{
	typedef std::pair<int64_t, int64_t> HashPair;
	const int64_t CHAR_SIZE = 26; // 字符集大小
	HashPair hashPow[N];
	const int64_t mod1 = 100000007LL,
			 	  mod2 = 100000037LL;

	/*
	 *	预处理函数
	 *	预处理出Hash所需的倍数模hashPow
	 */

	void preProcess()
	{
		hashPow[0] = std::make_pair(1LL, 1LL);
		for (int i = 1; i < N; i++)
		{
			hashPow[i].first  = hashPow[i - 1].first  * (CHAR_SIZE + 1LL) % mod1;
			hashPow[i].second = hashPow[i - 1].second * (CHAR_SIZE + 1LL) % mod2;
		}
	}
	/*
	 *	字符转换函数
	 *	将字符转换为Hash中的编号
	 */
	int64_t transChar(char ch)
	{
		return (int64_t)(ch - 'A' + 1);
	}
	
	/*
	 *	序列生成Hash生成函数
	 *  返回一个std::vector<HashPair>
	 *	储存生成出的Hash序列
	 */ 
	std::vector<HashPair> makeHash(std::string s)
	{
		size_t len = s.length();
		std::vector<HashPair> hashVal(len);
		for (size_t i = 0; i < len; i++)
		{
			hashVal[i].first  = (i > 0) ? (hashVal[i - 1].first  * (CHAR_SIZE + 1LL) + transChar(s[i])) % mod1
								   : transChar(s[i]) % mod1;
			hashVal[i].second = (i > 0) ? (hashVal[i - 1].second * (CHAR_SIZE + 1LL) + transChar(s[i])) % mod2
								   : transChar(s[i]) % mod1;						
		}
		return hashVal;
	}
	/*
	 *  截取某一段的Hash值
	 *	传入参数为[l, r)
	 *	即前闭后开形式
	 *  默认返回一个HashPair
	 */
	HashPair subHash(std::vector<HashPair> &hashVal, int l, int r)
	{
		if (l == 0)
			return hashVal[r - 1];
		else
		{
			HashPair result;
			result.first  = (hashVal[r - 1].first - 
							 hashVal[l - 1].first  * hashPow[r - l].first  % mod1 + mod1) % mod1;
			result.second = (hashVal[r - 1].second - 
							 hashVal[l - 1].second * hashPow[r - l].second % mod2 + mod2) % mod2;
			return result;
		}
	}
}

int n, m, k, q;

void work()
{
	std::string s, t;
	std::cin >> t >> s;
	auto a = stringHash::makeHash(s);
	auto hash = (*stringHash::makeHash(t).rbegin());
	int32_t len = t.length(), ans = 0;
	for (size_t i = len; i <= s.length(); i++)
		if (stringHash::subHash(a, i - len, i) == hash)
			ans++;
	std::cout << ans << '\n';
		
}
int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	stringHash::preProcess();
	int t;
	std::cin >> t;
	while (t --> 0)
		work();
}