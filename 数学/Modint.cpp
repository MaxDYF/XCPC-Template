template <const unsigned MOD>
class Modint
{
public:
	Modint() = default;
	Modint(unsigned int x) : val(x) {}
	unsigned int gnum() { return val; }
	friend istream &operator>>(istream &in, Modint &a) { return in >> a.val; }
	friend ostream &operator<<(ostream &out, Modint a) { return out << a.val; }
	friend Modint operator+(const Modint &a, const Modint &b) { return (a.val + b.val) % MOD; }
	friend Modint operator-(const Modint &a, const Modint &b) { return (a.val + MOD - b.val) % MOD; }
	friend Modint operator*(const Modint &a, const Modint &b) { return (1ULL * a.val * b.val) % MOD; }
	friend Modint operator/(const Modint &a, const Modint &b) { return a * __ksm(b.val); }
	friend Modint &operator*=(const Modint &a, const Modint &b) { return a = a * b; }
	friend Modint &operator+=(const Modint &a, const Modint &b) { return a = a + b; }
	friend Modint &operator-=(const Modint &a, const Modint &b) { return a = a - b; }
	friend Modint &operator/=(const Modint &a, const Modint &b) { return a = a / b; }
	friend Modint &operator++(Modint &a) { return a += 1; }
	friend Modint operator++(Modint &a, int)
	{
		Modint x = a;
		a += 1;
		return x;
	}
	friend Modint &operator--(Modint &a) { return a -= 1; }
	friend Modint operator--(Modint &a, int)
	{
		Modint x = a;
		a -= 1;
		return x;
	}
	friend bool operator==(Modint a, Modint b) { return a.x == b.x; }
	friend bool operator!=(Modint a, Modint b) { return !(a == b); }

private:
	int val;
	Modint __ksm(const Modint &base, long long k)
	{
		Modint ans = 1;
		while (k)
		{
			if (k & 1)
				ans *= base;
			base *= base;
			k /= 2;
		}
		return ans;
	}
};