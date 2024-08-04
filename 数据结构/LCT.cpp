#include <algorithm>
#include <iostream>
#include <vector>
/*
 * LCT模板
 * Info 表示值，Tag 表示标记
 */
template<typename _Info, typename _Tag>
class LCT{
public:
	LCT(): m_size(0){}
	LCT(const int& _n, const _Info& _v = _Info()){
		init(_n, _v);
	}
	LCT(const std::vector<_Info>& _init){
		init(_init);
	}
	void init(const int& _n, const _Info& _v = _Info()){
		init(std::vector<_Info>(_n, _v));
	}
	void init(const std::vector<_Info>& _init){
		resize(_init.size());
		for(size_t i = 0; i < m_size; ++i)
			val[i + 1] = _init[i];
	}
	void resize(const size_t& s){
		m_size = s;
		fa.resize(m_size + 1);
		siz.resize(m_size + 1);
		ch.resize(m_size + 1);
		sta.resize(m_size + 1);
		rev.resize(m_size + 1);
		val.resize(m_size + 1);
		sum.resize(m_size + 1);
		tag.resize(m_size + 1);
		for(size_t i = 0; i <= m_size; ++i)
			ch[i].resize(2);
	}
	size_t size()const{return m_size;}
	bool empty()const{return !m_size;}
	int findroot(int x){
		access(x);
		_splay(x);
		while(ch[x][0]){
			pushdown(x);
			x = ch[x][0];
		}
		_splay(x);
		return x;
	}
	void makeroot(const int& x){
		access(x);
		_splay(x);
		flip(x);
	}
	void link(const int& x, const int& y){
		makeroot(x);
		if(findroot(y) != x)
			fa[x] = y;
	}
	void cut(const int& x, const int& y){
		_split(x, y);
		if(findroot(y) == x && fa[y] == x && !ch[y][0]){
			fa[y] = ch[x][1] = 0;
			pushup(x);
		}
	}
	void set(const int& x, const _Info& v = _Info()){
		_splay(x);
		val[x] = v;
		pushup(x);
	}
	void change(const int& x, const int& y, const _Tag& v){
		_split(x, y);
		apply(y, v);
	}
	_Info asksum(const int& x, const int& y){
		_split(x, y);
		return sum[y];
	}
private:
	std::vector<int> fa, siz;
	std::vector<std::vector<int>> ch;
	std::vector<int> sta, rev;
	std::vector<_Info> val, sum;
	std::vector<_Tag> tag;
	size_t m_size;
	bool relation(const int& x)const{
		return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
	}
	void pushup(const int& x){
		sum[x] = sum[ch[x][0]] + val[x] + sum[ch[x][1]];
		siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
	}
	void flip(const int& x){
		std::swap(ch[x][0], ch[x][1]);
		rev[x] ^= 1;
	}
	void apply(const int& x, const _Tag& t){
		val[x].apply(t);
		sum[x].apply(t);
		tag[x].apply(t);
	}
	void pushdown(const int& x){
		if(rev[x]){
			if(ch[x][0]) flip(ch[x][0]);
			if(ch[x][1]) flip(ch[x][1]);
			rev[x] = 0;
		}
		if(ch[x][0]) apply(ch[x][0], tag[x]);
		if(ch[x][1]) apply(ch[x][1], tag[x]);
		tag[x] = _Tag();
	}
	void _rotate(const int& x){
		int y = fa[x], z = fa[y], k = (ch[y][1] == x), v = ch[x][!k];
		if(relation(y)) ch[z][ch[z][1] == y] = x;
		ch[x][!k] = y; ch[y][k] = v;
		if(v) fa[v] = y;
		fa[y] = x; fa[x] = z;
		pushup(y); pushup(x);
	}
	void _splay(int x){
		int y = x, top = 1;
		sta[top] = x;
		while(relation(y))
			sta[++top] = y = fa[y];
		while(top)
			pushdown(sta[top--]);
		while(relation(x)){
			y = fa[x]; top = fa[y];
			if(relation(y))
				_rotate((ch[y][1] == x) == (ch[top][1] == y)? y: x);
			_rotate(x);
		}
		pushup(x);
	}
	void access(int x){
		for(int y = 0; x; y = x, x = fa[x]){
			_splay(x);
			ch[x][1] = y;
			pushup(x);
		}
	}
	void _split(const int& x, const int& y){
		makeroot(x);
		access(y);
		_splay(y);
	}
};
typedef long long i64;
const i64 mod = 998244353;
struct Tag{
	i64 add, mul;
	Tag(i64 vadd = 0, i64 vmul = 1): add(vadd), mul(vmul){}
	void apply(const Tag& v){
		mul *= v.mul; mul %= mod;
		add *= v.mul; add += v.add; add %= mod;
	}
};
struct Info{
	i64 sum, siz;
	Info(i64 v = 0, i64 z = 0): sum(v % mod), siz(z){}
	void apply(const Tag& v){
		sum = (sum * v.mul % mod + v.add * siz % mod) % mod;
	}
	Info operator +(const Info& b)const{
		return Info(sum + b.sum, siz + b.siz);
	}
};
LCT<Info, Tag> tr;