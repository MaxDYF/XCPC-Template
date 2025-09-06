/*
 * 矩阵类
 * 实现了矩阵加法、减法、乘法以及取模
 */
template <class T> class Matrix {
  private:
    int32_t R, C;
    std::vector<std::vector<T>> a;

  public:
    /*
     * 需要在初始化时传入其行数Rt与列数Ct
     * 可选参数为矩阵初始初始值init_val
     */
    Matrix(const int Rt, const int Ct, T init_val = 0) {
        a = std::vector<std::vector<T>>(Rt, std::vector<T>(Ct, init_val));
        R = Rt;
        C = Ct;
    }
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        R = init.size();
        if (R == 0) {
            C = 0;
            a = {};
            return;
        }
        C = init.begin()->size();
        for (const auto &row : init) {
            if (row.size() != C) {
                throw std::invalid_argument("All rows must have the same number of columns");
            }
        }
        a.reserve(R);
        for (const auto &row : init) {
            a.push_back(std::vector<T>(row));
        }
    }
    void init(std::initializer_list<std::initializer_list<T>> a) { (*this) = Matrix<T>(a); }
    Matrix<T> operator*(const Matrix<T> b) {
        try {
            if (C != b.R)
                throw "SIZE DIFF";
        } catch (std::string code) {
            std::cerr << "MATRIX ERROR @ OPERATOR * : " + code << std::endl;
            exit(0);
        }
        Matrix<T> c(R, b.C, 0);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < b.C; j++)
                for (int k = 0; k < C; k++)
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]);
        return c;
    }
    Matrix<T> operator+(const Matrix<T> b) {
        try {
            if (R != b.R || C != b.C)
                throw "SIZE DIFF";
        } catch (std::string code) {
            std::cerr << "MATRIX ERROR @ OPERATOR + : " + code << std::endl;
            exit(0);
        }
        Matrix<T> c(R, C, 0);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                c.a[i][j] = (a[i][j] + b.a[i][j]);

        return c;
    }
    Matrix<T> operator*(const T val) {
        Matrix<T> c(a);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                c.a[i][j] = (c.a[i][j] * val);
        return c;
    }
    Matrix &operator+=(const Matrix<T> &b) { return a = a + b; }
    Matrix &operator-=(const Matrix<T> &b) { return a = a - b; }
    Matrix &operator*=(const Matrix<T> &b) { return a = a * b; }
    T sum() {
        T ans = 0;
        for (auto line : a)
            for (auto x : line)
                ans = (ans + x);
        return ans;
    }
    auto getVec() { return a; }
    Matrix transpos() {
        Matrix<T> b(C, R);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                b.a[j][i] = a[i][j];
        return b;
    }
};