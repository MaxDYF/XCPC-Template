template <typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols, const T& initial_value = T())
        : rows_(rows), cols_(cols), data_(rows, std::vector<T>(cols, initial_value)) {}
 
 
    // 重载()运算符用于访问行列列
    T& operator()(size_t row, size_t col) {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            //std::cerr << "Error: Index out of bounds\n";
            // 返回一个默认值
            static T default_value = 0;
            return default_value;
        }
        return data_[row][col];
    }
 
    // 用于获取行数和列数的函数
    size_t rows() const {
        return rows_;
    }
 
    size_t cols() const {
        return cols_;
    }
 
private:
    size_t rows_;
    size_t cols_;
    std::vector<std::vector<T>> data_;
};

