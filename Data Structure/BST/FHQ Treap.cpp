#include <bits/stdc++.h>
using namespace std;
template<class T>
class Tree
{
private:
    struct Node
    {
        /* data */
        int son[2], rand, size;
        T val;
        bool tag;
    };
    vector<Node> tr;
    int root, seed, cnt;
    int rand() {
        return seed = ((long long)(seed) * 238973) % 2147483647;
    }
    int add(T val) {
        tr.push_back(Node{{0, 0}, rand(), 1, val, 0});
        return tr.size() - 1;
    }
    void spread(int now) {
        if(!tr[now].tag)
            return;
        swap(tr[now].son[0], tr[now].son[1]);
        tr[tr[now].son[0]].tag ^= 1;
        tr[tr[now].son[1]].tag ^= 1;
        tr[now].tag = 0;
    }
    void updata(int now) {
        tr[now].size = tr[tr[now].son[0]].size + tr[tr[now].son[1]].size + 1;
    }
    void split(int now, int &a, int &b, int val) {
        if(!now) {
            a = b = 0;
            return;
        }
        spread(now);
        if(tr[tr[now].son[0]].size + 1 <= val) {
            a = now;
            split(tr[now].son[1], tr[now].son[1], b, val - tr[tr[now].son[0]].size - 1);
        } else {
            b = now;
            split(tr[now].son[0], a, tr[now].son[0], val);
        }
        updata(now);
    }
    int merge(int a, int b) {
        if(!a || !b) {
            return a | b;
        }
        if(tr[a].rand < tr[b].rand) {
            spread(a);
            tr[a].son[1] = merge(tr[a].son[1], b);
            updata(a);
            return a;
        }
        else {
            spread(b);
            tr[b].son[0] = merge(a, tr[b].son[0]);
            updata(b);
            return b;
        }
    }
    void printF(int now) {
    	spread(now);
        if(tr[now].son[0])
            printF(tr[now].son[0]);
        cout << tr[now].val << ' ';
        if(tr[now].son[1])
            printF(tr[now].son[1]);
    }
public:
    Tree() {
        tr.push_back(Node{{0, 0}, rand(), 0, -2147483647, 0});
        seed = 19260817;
    };
    void get(T *a, int begin, int end) {
        for(auto i = begin; i <= end; i++)
            root = merge(root, add(a[i]));
    }
    void reverse(int l, int r) {
        int left , right, pos;
        split(root, left, right, r);
        split(left, left, pos, l - 1);
        tr[pos].tag ^= 1;
        root = merge(merge(left, pos), right); ;
    }
    
    void print() {
        printF(root);
    }
};
Tree<int> a;
int num[1000000];
int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) 
        num[i] = i;
    a.get(num, 1, n);
    for(int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        a.reverse(l, r);
    }
    a.print();
}