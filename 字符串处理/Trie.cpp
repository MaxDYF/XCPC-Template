#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
typedef long long i64;
class Trie
{
public:
    Trie() : m_size(1)
    {
        tree.clear();
        tree.push_back(Node(-1, 0));
    }
    ~Trie() {}
    int size() const { return m_size; }
    int insert(char *s, int len)
    {
        int now = 0;
        for (int i = 0; i < len; ++i)
        {
            if (!tree[now].nxt.count(s[i]))
            {
                tree[now].nxt[s[i]] = m_size++;
                tree.push_back(Node(now, s[i]));
            }
            now = tree[now].nxt[s[i]];
        }
        return now;
    }
    friend class SAM;

private:
    struct Node
    {
        int fa;
        char c;
        std::map<char, int> nxt;
        Node(int _1, char _2) : fa(_1), c(_2)
        {
            nxt.clear();
        }
    };
    std::vector<Node> tree;
    int m_size;
};