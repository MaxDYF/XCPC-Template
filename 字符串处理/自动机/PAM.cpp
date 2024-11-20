class PAM
{
private:
    struct Node
    {
        int fail;
        int cnt;
        int len;
        int son[26];
        Node()
        {
            fail = 0;
            len = 0;
            cnt = 0;
            memset(son, 0, sizeof son);
        }
        Node(int len)
        {
            *this = Node();
            this->len = len;
        }
    };
    vector<Node> tr;
    string str;
    vector<int> id2Node;
    int lst;
    vector<vector<int>> fa;
    int getfail(int x, int i)
    {
        while (i - tr[x].len - 1 < 0 || str[i - tr[x].len - 1] != str[i])
            x = tr[x].fail;
        return x;
    }
    int newnode(int len)
    {
        tr.push_back(Node(len));
        return tr.size() - 1;
    }

public:
    PAM()
    {
        lst = 0;
        tr.clear();
        newnode(0);
        newnode(-1);
        str.push_back('#');
        tr[1].fail = 1;
        tr[0].fail = 1;
    }
    void insert(char c)
    {
        str.push_back(c);
        int i = str.length() - 1;
        int x = getfail(lst, i);
        if (!tr[x].son[c - 'a'])
        {
            int p = newnode(tr[x].len + 2);
            int f = getfail(tr[x].fail, i);
            tr[p].fail = tr[f].son[c - 'a'];
            tr[x].son[c - 'a'] = p;
            tr[p].cnt = tr[tr[p].fail].cnt + 1;
        }
        lst = tr[x].son[c - 'a'];
        id2Node.push_back(lst);
    }
    void buildFailTree()
    {
        int n = tr.size();
        fa = vector<vector<int>>(n, vector<int>(25));
        for (int x = 0; x < n; x++)
        {
            fa[x][0] = tr[x].fail;
            for (int i = 1; i < 25; i++)
                fa[x][i] = fa[fa[x][i - 1]][i - 1];
        }
    }
};