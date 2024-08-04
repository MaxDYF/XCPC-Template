#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <string>
#include <vector>
typedef long long i64;

class Trie{
public:
	Trie(): m_size(1){
		tree.clear();
		tree.push_back(Node(-1, 0));
	}
	virtual ~Trie(){}
	virtual int size()const{return m_size;}
	int insert(char* s, int len){
		int now = 0;
		for(int i = 0; i < len; ++i){
			if(!tree[now].nxt.count(s[i])){
				tree[now].nxt[s[i]] = m_size++;
				tree.push_back(Node(now, s[i]));
			}
			now = tree[now].nxt[s[i]];
		}
		return now;
	}
protected:
	struct Node{
		int fa, lst; char c;
		std::map<char, int> nxt;
		Node(int _1, char _2): fa(_1), lst(0), c(_2){
			nxt.clear();
		}
	};
	std::vector<Node> tree;
	int m_size;
};

class SAM: public Trie{
public:
	SAM(): m_size(1), _lst(0){
		seq.clear();
		seq.push_back(state(0, -1));
	}
	virtual ~SAM(){}
	int size()const{return m_size;}
	void build(){
		std::queue<int> q;
		for(int t = 0; t < 26; ++t)
		if(~Trie::tree[0].nxt[t])
			q.push(Trie::tree[0].nxt[t]);
		Trie::tree[0].lst = 0;
		while(!q.empty()){
			int x = q.front(); q.pop();
			Trie::tree[x].lst = saminsert(Trie::tree[x].c, Trie::tree[Trie::tree[x].fa].lst);
			for(int t = 0; t < 26; ++t)
			if(~Trie::tree[x].nxt[t])
				q.push(Trie::tree[x].nxt[t]);
		}
	}
	friend i64 calc(SAM& sam);
private:
	struct state{
		int len, link, cnt;
		std::map<char, int> nxt;
		state(int _1, int _2, int _3 = 0): len(_1), link(_2), cnt(_3){
			nxt.clear();
		}
	};
	std::vector<state> seq;
	int m_size, _lst;
	int saminsert(char c, int lst){
		if(seq[lst].nxt.count(c)){
			int p = lst, q = seq[lst].nxt[c];
			if(seq[q].len == seq[p].len + 1) return q;
			else{
				int r = m_size++;
				seq.push_back(state(seq[p].len + 1, seq[q].link, 0));
				seq[r].nxt = seq[q].nxt;
				seq[q].link = r;
				while(~p && seq[p].nxt.count(c) && seq[p].nxt[c] == q){
					seq[p].nxt[c] = r;
					p = seq[p].link;
				}
				return r;
			}
		}
		int cur = m_size++;
		seq.push_back(state(seq[lst].len + 1, -1, 1));
		int p = lst;
		lst = cur;
		while(~p && !seq[p].nxt.count(c)){
			seq[p].nxt[c] = cur;
			p = seq[p].link;
		}
		if(p == -1){
			seq[cur].link = 0;
		}
		else{
			int q = seq[p].nxt[c];
			if(seq[q].len == seq[p].len + 1){
				seq[cur].link = q;
			}
			else{
				int r = m_size++;
				seq.push_back(state(seq[p].len + 1, seq[q].link, 0));
				seq[r].nxt = seq[q].nxt;
				seq[cur].link = seq[q].link = r;
				while(~p && seq[p].nxt.count(c) && seq[p].nxt[c] == q){
					seq[p].nxt[c] = r;
					p = seq[p].link;
				}
			}
		}
		return cur;
	}
};
const int N = 1000010;
char str[N];
int buc[N << 1], pos[N << 1];
SAM sam;
i64 calc(SAM& sam){
	i64 ans = 0;
	for(int i = 1; i < sam.size(); ++i) buc[sam.seq[i].len]++;
	for(int i = 1; i < sam.size(); ++i) buc[i] += buc[i - 1];
	for(int i = sam.size() - 1; i; --i) pos[buc[sam.seq[i].len]--] = i;
	for(int i = sam.size() - 1; i; --i){
		int p = pos[i];
		sam.seq[sam.seq[p].link].cnt += sam.seq[p].cnt;
		if(sam.seq[p].cnt > 1){
		//	printf("%d %d\n", sam.seq[p].cnt, sam.seq[p].len);
			ans = std::max(ans, 1ll * sam.seq[p].cnt * sam.seq[p].len);
		}
	}
	return ans;
}
// For the array version of nxt[], see P6139.cpp