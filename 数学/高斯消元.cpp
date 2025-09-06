
std::vector<int> gauss(std::vector<std::vector<int>> a, std::vector<int> b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        int r = i;
        while (a[r][i] == 0)
            ++r;
        std::swap(a[i], a[r]);
        std::swap(b[i], b[r]);
        int inv = power(a[i][i], P - 2);
        for (int j = i; j < n; ++j)
            a[i][j] = 1ll * a[i][j] * inv % P;
        b[i] = 1ll * b[i] * inv % P;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            int x = a[j][i];
            for (int k = i; k < n; ++k)
                a[j][k] = (a[j][k] + 1ll * (P - x) * a[i][k]) % P;
            b[j] = (b[j] + 1ll * (P - x) * b[i]) % P;
        }
    }
    return b;
}

std::vector<double> gauss(std::vector<std::vector<double>> a, std::vector<double> b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        double x = a[i][i];
        for (int j = i; j < n; ++j)
            a[i][j] /= x;
        b[i] /= x;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            x = a[j][i];
            for (int k = i; k < n; ++k)
                a[j][k] -= a[i][k] * x;
            b[j] -= b[i] * x;
        }
    }
    return b;
}