// #pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef std::pair<int, int> HashPair;
class Hash
{
private:
    const int CHAR_SIZE = 26; // 字符集大小
    const int CC = (CHAR_SIZE + 1LL);
    std::vector<HashPair> hashPow;
    std::vector<HashPair> hashVal;
    const int mod1 = 100000007,
              mod2 = 100000037;
    /*
     *    字符转换函数
     *    将字符转换为Hash中的编号
     */
    int transChar(char ch)
    {
        return (ch - 'A' + 1);
    }
    /*
     *    序列生成Hash生成函数并储存
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
            hashPow[i].first = (int64_t)hashPow[i - 1].first * CC % mod1;
            hashPow[i].second = (int64_t)hashPow[i - 1].second * CC % mod2;
        }
        for (size_t i = 0; i < len; i++)
        {
            int p = transChar(s[i]);
            if (i > 0)
            {
                hashVal[i].first = ((int64_t)hashVal[i - 1].first * CC + p) % mod1;
                hashVal[i].second = ((int64_t)hashVal[i - 1].second * CC + p) % mod2;
            }
            else
            {
                hashVal[i].first = transChar(s[i]) % mod1;
                hashVal[i].second = transChar(s[i]) % mod2;
            }
        }
    }

public:
    Hash(std::string &str)
    {
        makeHash(str);
    }
    /*
     *  截取某一段的Hash值
     *    传入参数为[l, r]
     *  默认返回一个HashPair
     */
    HashPair subHash(int l, int r)
    {
        if (l > r)
            return {0, 0};
        if (l == 0)
            return hashVal[r];
        else
        {
            HashPair result;
            auto c1 = (int64_t)hashVal[l - 1].first * hashPow[r - l + 1].first % mod1;
            result.first = ((int64_t)hashVal[r].first - c1 + mod1) % mod1;
            auto c2 = (int64_t)hashVal[l - 1].second * hashPow[r - l + 1].second % mod2;
            result.second = ((int64_t)hashVal[r].second - c2 + mod2) % mod2;
            return result;
        }
    }
};