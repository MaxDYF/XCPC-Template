template <class T>
class SplayTree
{
private:
#define LEFTSON 0
#define RIGHTSON 1
    struct Node
    {
        T val;
        int son[2];
        int fa;
        int siz;
        Node()
        {
            val = T();
            son[LEFTSON] = son[RIGHTSON] = 0;
            fa = siz = 0;
        }
        Node(T val, int cnt = 1)
        {
            this->val = val;
            this->siz = 1;
            this->son[0] = this->son[1] = 0;
        }
    };
    vector<Node> tr;
    int root;
    /* 更新旋转后节点的信息 */
    void update(int x)
    {
        tr[x].siz = tr[tr[x].son[LEFTSON]].siz + tr[tr[x].son[RIGHTSON]].siz + 1;
    }
    /*返回当前编号的节点是左节点还是右节点*/
    int identify(int x)
    {
        if (tr[tr[x].fa].son[1] == x)
            return RIGHTSON;
        else
            return LEFTSON;
    }
    /*根据情况进行左旋Zig或者右旋Zag*/
    void rotate(int x)
    {
        int y = tr[x].fa, z = tr[y].fa;
        int type = identify(x), typeY = 0;
        if (z)
            tr[z].son[identify(y)] = x;
        tr[y].son[type] = tr[x].son[!type];
        if (tr[x].son[!type])
            tr[tr[x].son[!type]].fa = y;
        tr[x].son[!type] = y;
        tr[y].fa = x;
        tr[x].fa = z;
        update(y);
        update(x);
    }
    /*伸展操作，将节点旋转至目标点*/
    void splay(int x, int target = 0)
    {
        if (x == target)
            return;
        while (tr[x].fa != target)
        {
            int y = tr[x].fa;
            if (tr[y].fa == 0) // 单Zig/Zag
                rotate(x);
            else
            {
                int typeX = identify(x), typeY = identify(y);
                if (typeX == typeY) // 同向，ZigZig/ZagZag
                {
                    rotate(y);
                    rotate(x);
                }
                else // 异向，ZigZag/ZagZig
                {
                    rotate(x);
                    rotate(x);
                }
            }
        }
        if (target == 0)
            root = x;
    }

public:
    SplayTree()
    {
        tr.clear();
        tr.push_back(Node());
        root = 0;
    }
    void insert(T x)
    {
        if (root == 0)
        {
            tr.push_back(Node(x));
            root = tr.size() - 1;
        }
        else
        {
            int p = root, pf = 0;
            bool type = 0;
            while (p)
            {
                pf = p;
                type = x > tr[p].val;
                p = tr[p].son[type];
            }
            tr.push_back(Node(x));
            p = tr.size() - 1;
            tr[pf].son[type] = p;
            tr[p].fa = pf;
            splay(p);
        }
    }
    void remove(T val)
    {
        int p = root, pf = 0;
        while (p && tr[p].val != val)
        {
            pf = p;
            p = tr[p].son[val > tr[p].val];
        }
        if (!p)
        {
            if (pf)
                splay(pf);
            return;
        }
        splay(p);
        int cur = tr[p].son[0];
        if (cur == 0)
        {
            root = tr[p].son[1];
            tr[root].fa = 0;
            tr[p] = Node();
            return;
        }
        root = cur;
        while (tr[cur].son[1])
            cur = tr[cur].son[1];
        tr[cur].son[1] = tr[p].son[1];
        tr[tr[p].son[1]].fa = cur;
        tr[root].fa = 0;
        tr[p] = Node();
        splay(cur);
    }
    T find_by_rank(int rank)
    {
        int nowRank = 0, p = root;
        while (true)
        {
            if (nowRank + tr[tr[p].son[0]].siz + 1 == rank)
            {
                splay(p);
                return tr[p].val;
            }
            else if (nowRank + tr[tr[p].son[0]].siz >= rank)
                p = tr[p].son[0];
            else
            {
                nowRank += tr[tr[p].son[0]].siz + 1;
                p = tr[p].son[1];
            }
        }
    }
    int order_by_rank(T val)
    {
        int rank = 0, p = root, pf = 0;
        while (p != 0)
        {
            pf = p;
            if (tr[p].val < val)
            {
                rank += tr[tr[p].son[0]].siz + 1;
                p = tr[p].son[1];
            }
            else
                p = tr[p].son[0];
        }
        splay(pf);
        return rank + 1;
    }
    T prev(T val)
    {
        T ans = T();
        int p = root, pf = 0;
        while (p != 0)
        {
            pf = p;
            if (tr[p].val >= val)
                p = tr[p].son[0];
            else
            {
                ans = tr[p].val;
                p = tr[p].son[1];
            }
        }
        splay(pf);
        return ans;
    }
    T next(T val)
    {
        T ans = T();
        int p = root, pf = 0;
        while (p != 0)
        {
            pf = p;
            if (tr[p].val <= val)
                p = tr[p].son[1];
            else
            {
                ans = tr[p].val;
                p = tr[p].son[0];
            }
        }
        splay(pf);
        return ans;
    }
#undef LEFTSON
#undef RIGHTSON
};