#include <algorithm>
#include <cstdint>
#include <vector>
/*
 * RMQ算法模板
 * 默认维护区间最大值
 */
namespace RMQ {
typedef int32_t T;
// 维护值的类型，默认为int32_t
std::vector<std::vector<T>> _data;
// 预处理出log2以提速
std::vector<int32_t> lg2;
// 定义维护的信息，默认为max
T func(T x, T y) { return std::max(x, y); }
void init(std::vector<T> a) {
    int n = a.size();
    lg2 = std::vector<int>(n + 1);
    lg2[1] = 0;
    for (int i = 2; i <= n; i++)
        lg2[i] = lg2[i >> 1] + 1;
    _data = std::vector<std::vector<int>>(n, std::vector<int>(lg2[n] + 1));
    for (int i = 0; i < n; i++)
        _data[i][0] = a[i];
    for (int bit = 1; bit <= lg2[n]; bit++)
        for (int i = 0; i + (1 << bit) - 1 < n; i++)
            _data[i][bit] = func(_data[i][bit - 1], _data[i + (1 << (bit - 1))][bit - 1]);
}
T query(size_t l, size_t r) {
    int32_t bit = lg2[r - l + 1];
    return func(_data[l][bit], _data[r - (1 << bit) + 1][bit]);
}
} // namespace RMQ