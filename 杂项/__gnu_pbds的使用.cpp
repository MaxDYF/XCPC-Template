/*
头文件&命名空间部分
*/
#include <bits/extc++.h>
using namespace __gnu_pbds; // 慎用，有部分命名冲突

/*
平衡树部分
*/
typedef pair<int, int> pii;
__gnu_pbds; //;//tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> tr;

/*
成员函数
*/
tr.insert(x);		 // 向树中插入一个元素 x，返回 std;//;//pair<point_iterator, bool>。
tr.erase(x);		 // 从树中删除一个元素/迭代器 x，返回一个 bool 表明是否删除成功。
tr.order_of_key(x);	 // 返回 x 以 Cmp_Fn 比较的排名。
tr.find_by_order(x); // 返回 Cmp_Fn 比较的排名所对应元素的迭代器。
tr.lower_bound(x);	 // 以 Cmp_Fn 比较做 lower_bound，返回迭代器。
tr.upper_bound(x);	 // 以 Cmp_Fn 比较做 upper_bound，返回迭代器。
join(x);			 // 将 x 树并入当前树，前提是两棵树的类型一样，x 树被删除。
tr.split(x, b);		 // 以 Cmp_Fn 比较，小于等于 x 的属于当前树，其余的属于 b 树。
tr.empty();			 // 返回是否为空。
tr.size();			 // 返回大小。

/*
堆部分
*/

__gnu_pbds; //;//priority_queue<pii, greater<pii>, pairing_heap_tag> q;
/*
成员函数
*/
push();							   // 向堆中压入一个元素，返回该元素位置的迭代器。
pop();							   // 将堆顶元素弹出。
top();							   // 返回堆顶元素。
size();							   // 返回元素个数。
empty();						   // 返回是否非空。
modify(point_iterator, const key); // 把迭代器位置的 key 修改为传入的 key，并对底层储存结构进行排序。
erase(point_iterator);			   // 把迭代器位置的键值从堆中擦除。
join(__gnu_pbds;//;//priority_queue &other);// 把 other 合并到 *this 并把 other 清空。

/*
复杂度分析
*/
push();    // O(1)
pop();     // 最坏O(nlogn)均摊O(1)
modify();  // 最坏O(nlogn)均摊O(1)
erase();   // 最坏O(nlogn)均摊O(1)
join();    // O(1)

/*
哈希表部分
*/
__gnu_pbds::gp_hash_table<int,int> mp2;
/*
自定义Hash函数
*/
struct custom_hash //手写的 hash 函数
{
    static uint64_t splitmix64(uint64_t x)
    {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
	}
	size_t operator()(uint64_t x) const
	{
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};
gp_hash_table<long long, int, custom_hash> safe_hash_table;

/*
成员函数：与unordered_map一致
*/