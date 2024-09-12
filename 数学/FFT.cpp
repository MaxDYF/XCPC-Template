#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

const double PI = std::acos(-1);

class Complex
{
public:
	Complex(double _real = 0, double _virtual = 0);
	double getReal() const;
	double getVirtual() const;
	Complex operator+(const Complex &b) const;
	Complex operator-(const Complex &b) const;
	Complex operator*(const Complex &b) const;

private:
	double x, y;
};
Complex::Complex(double _real, double _virtual) : x(_real), y(_virtual) {}
double Complex::getReal() const { return this->x; }
double Complex::getVirtual() const { return this->y; }
Complex Complex::operator+(const Complex &b) const
{
	return Complex(this->x + b.x, this->y + b.y);
}
Complex Complex::operator-(const Complex &b) const
{
	return Complex(this->x - b.x, this->y - b.y);
}
Complex Complex::operator*(const Complex &b) const
{
	return Complex(this->x * b.x - this->y * b.y, this->x * b.y + this->y * b.x);
}

/* recursive FFT
void FFT(std::vector<Complex>& A, int flag = 1){
	int n = A.size();
	if(n == 1) return;
	std::vector<Complex> A1(n >> 1), A2(n >> 1);
	for(int i = 0; i < (n >> 1); ++i)
		A1[i] = A[i << 1],
		A2[i] = A[i << 1 | 1];
	FFT(A1, flag); FFT(A2, flag);
	Complex w1(std::cos(2.0 * PI / n), std::sin(2.0 * PI / n) * flag), wk(1, 0);
	for(int k = 0; k < (n >> 1); wk = wk * w1, ++k)
		A[k] = A1[k] + A2[k] * wk,
		A[k + (n >> 1)] = A1[k] - A2[k] * wk;
}
*/

// make reversed binary representation array
std::vector<int> makerev(const int &len)
{
	std::vector<int> ans;
	ans.emplace_back(0);
	ans.emplace_back(len >> 1);
	int l = 0;
	while ((1 << l) < len)
		l++;
	for (int i = 2; i < len; ++i)
		ans.emplace_back(ans[i >> 1] >> 1 | (i & 1) << (l - 1));
	/*
		ans[i >> 1] is the reversed representation of i >> 1
		(i >> 1) << 1 = i, so in reversed representation we need ans[i >> 1] >> 1
		if i & 1 == 1, then the MSB of reversed representation should be 1
		that is (i & 1) << (l - 1)
	*/
	return ans;
}

// iterative FFT
void FFT(std::vector<Complex> &A, const int &flag = 1)
{
	static std::vector<int> rev;
	int n = A.size();
	if (int(rev.size()) != n)
		rev.clear(),
			rev = makerev(n);
	for (int i = 0; i < n; ++i)
		if (rev[i] > i)
			std::swap(A[i], A[rev[i]]);
	for (int len = 2, m = 1; len <= n; m = len, len <<= 1)
	{
		Complex w1(std::cos(2.0 * PI / len), std::sin(2.0 * PI / len) * flag), wk;
		for (int l = 0, r = len; r <= n; l += len, r += len)
		{
			wk = Complex(1, 0);
			for (int k = l; k < l + m; wk = wk * w1, ++k)
			{
				Complex x = A[k] + A[k + m] * wk,
						y = A[k] - A[k + m] * wk;
				A[k] = x;
				A[k + m] = y;
			}
		}
	}
}

signed main(int argc, char **argv)
{
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m, len = 1;
	std::cin >> n >> m;
	while (len <= (n + m))
		len <<= 1; // to make the length a power of 2
	std::vector<Complex> A(len), B(len);
	for (int i = 0, x; i <= n; ++i)
	{
		std::cin >> x;
		A[i] = Complex(x, 0);
	}
	for (int i = 0, x; i <= m; ++i)
	{
		std::cin >> x;
		B[i] = Complex(x, 0);
	}
	FFT(A);
	FFT(B);
	for (int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(A, -1);
	for (int i = 0; i <= (n + m); ++i)
		std::cout << int(A[i].getReal() / len + 0.5) << ' ';
	std::cout << std::endl;
	return 0;
}