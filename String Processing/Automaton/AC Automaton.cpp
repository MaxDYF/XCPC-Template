// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int inf = 1 << 30;
const long long llinf = 1ll << 60;
const double PI = acos(-1);

#define lowbit(x) (x & -x)
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
typedef pair<ll, int> pli;

/*
 * AC自动机模板
 * 本模板使用了建图优化以及拓扑排序
 * 最终第i个模式串匹配文本串次数为 vis[rev[i]]
 * 模板题https://www.luogu.com.cn/problem/P5357
 */
namespace ACautomaton
{
    struct TrieNode
    {
        int son[26];
        int fail;
        int flag;
        int ans;
        TrieNode()
        {
            memset(son, 0, sizeof son);
            fail = flag = ans = 0;
        }
        void clear(void)
        {
            (*this) = TrieNode();
        }
    };
    TrieNode trie[N];
    int vis[N];   // 记录能匹配到当前点的答案。
    int rev[N];   // 索引，将第i个模式索引至答案的下标，作用是模式串去重
    int indeg[N]; // getfail()所求的入度，用于拓扑排序
                  // 注意，indeg[]的入度是fail边的入度
    int cnt = 1;
    /*
     * 插入一个模式串str, 其编号为num
     */
    void insert(string &str, int num)
    {
        int u = 1;
        for (auto ch : str)
        {
            int v = ch - 'a';
            if (trie[u].son[v] == 0)
                trie[u].son[v] = ++cnt;
            u = trie[u].son[v];
        }
        if (!trie[u].flag)
            trie[u].flag = num;
        rev[num] = trie[u].flag;
    }
    /*
     * 构建fail指针
     * 为拓扑排序建立入度
     */
    void getfail(void)
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            trie[0].son[i] = 1;
        trie[1].fail = 0;
        q.push(1);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            int fail = trie[u].fail;
            for (int i = 0; i < 26; i++)
            {
                // 减去了跳fail边的操作
                // 直接将儿子节点连到fail节点的对应儿子节点
                // 相当于将fail边路径压缩
                if (trie[u].son[i] == 0)
                {
                    trie[u].son[i] = trie[fail].son[i];
                    continue;
                }
                int v = trie[u].son[i],
                    nextFail = trie[fail].son[i];
                indeg[nextFail]++;
                trie[v].fail = nextFail;
                q.push(v);
            }
        }
    }
    /*
     * 导入待查寻的文本串
     * 将匹配的路径记录到TrieNode::ans上
     * 以便拓扑排序时求解
     */
    void query(string &str)
    {
        int u = 1;
        for (auto ch : str)
        {
            u = trie[u].son[ch - 'a'];
            trie[u].ans++;
        }
    }
    /*
     * 关键步骤拓扑排序
     * 求解匹配答案
     */
    void topu(void)
    {
        std::queue<int> q;
        for (int i = 1; i <= cnt; i++)
            if (indeg[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (trie[u].flag != 0)
                vis[trie[u].flag] = trie[u].ans;
            int fail = trie[u].fail;
            trie[fail].ans += trie[u].ans;
            --indeg[fail];
            if (indeg[fail] == 0)
                q.push(fail);
        }
    }
    /*
     *  返回第num个模式串对应的答案
     */
    int getAnswer(int num)
    {
        return vis[rev[num]];
    }
}

int n, m, k, q;

void work()
{
    cin >> n;
    string s, t;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        ACautomaton::insert(s, i);
    }
    cin >> t;
    ACautomaton::getfail();
    ACautomaton::query(t);
    ACautomaton::topu();
    for (int i = 1; i <= n; i++)
        cout << ACautomaton::getAnswer(i) << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    work();
}