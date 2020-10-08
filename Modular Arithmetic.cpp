template<const int &MOD>
struct _m_int  // This is our new type which will do operations under modulo MOD
{
	int val;   // Value of variable

	_m_int(int64_t v = 0)  // Typecasting into our data type from 64 bit integer
	{
		if (v < 0) v = v % MOD + MOD;
		if (v >= MOD) v %= MOD;
		val = v;
	}

	static int mod_inv(int a, int m = MOD)
	{
		// https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
		int g = m, r = a, x = 0, y = 1;

		while (r != 0)
		{
			int q = g / r;
			g %= r; swap(g, r);
			x -= q * y; swap(x, y);
		}

		return x < 0 ? x + m : x;
	}

	explicit operator int() const
	{
		return val;
	}

	explicit operator int64_t() const
	{
		return val;
	}

	_m_int& operator += (const _m_int &other)  // Addition
	{
		val -= MOD - other.val;
		if (val < 0) val += MOD;
		return *this;
	}

	_m_int& operator -= (const _m_int &other)  // Subtraction
	{
		val -= other.val;
		if (val < 0) val += MOD;
		return *this;
	}

	static unsigned fast_mod(uint64_t x, unsigned m = MOD) // Mod operation
	{
#if !defined(_WIN32) || defined(_WIN64)
		return x % m;
#endif
		// Optimized mod for Codeforces 32-bit machines.
		// x must be less than 2^32 * m for this to work, so that x / m fits in a 32-bit integer.
		unsigned x_high = x >> 32, x_low = (unsigned) x;
		unsigned quot, rem;
		asm("divl %4\n"
		    : "=a" (quot), "=d" (rem)
		    : "d" (x_high), "a" (x_low), "r" (m));
		return rem;
	}

	_m_int& operator*=(const _m_int &other)  // Multiplication
	{
		val = fast_mod((uint64_t) val * other.val);
		return *this;
	}

	_m_int& operator/=(const _m_int &other)  // Division
	{
		return *this *= other.inv();
	}

	friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
	friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
	friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
	friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }

	_m_int& operator++()  // Pre-increment
	{
		val = val == MOD - 1 ? 0 : val + 1;
		return *this;
	}

	_m_int& operator--()  // Pre-decrement
	{
		val = val == 0 ? MOD - 1 : val - 1;
		return *this;
	}

	_m_int operator++(int) { _m_int before = *this; ++*this; return before; }  // Post increment
	_m_int operator--(int) { _m_int before = *this; --*this; return before; }  // Post decrement

	_m_int operator-() const  // Change sign
	{
		return val == 0 ? 0 : MOD - val;
	}

	// Boolean operators
	bool operator==(const _m_int &other) const { return val == other.val; }
	bool operator!=(const _m_int &other) const { return val != other.val; }
	bool operator< (const _m_int &other) const { return val <  other.val; }
	bool operator<=(const _m_int &other) const { return val <= other.val; }
	bool operator> (const _m_int &other) const { return val >  other.val; }
	bool operator>=(const _m_int &other) const { return val >= other.val; }

	_m_int inv() const  // Calculating inverse
	{
		return mod_inv(val);
	}

	_m_int pow(int64_t p) const  // Calculating power
	{
		if (p < 0)
			return inv().pow(-p);

		_m_int a = *this, result = 1;

		while (p > 0)
		{
			if (p & 1)
			{
				result *= a;
			}
			a *= a;
			p >>= 1;
		}

		return result;
	}

	friend ostream& operator<<(ostream &os, const _m_int &m)  // Writing output
	{
		return os << m.val;
	}

};

extern const int MOD = 998244353;
using mod_int = _m_int<MOD>;


// Problem: https://codeforces.com/contest/1400/problem/G
// Solution: https://pastebin.com/BUzfm1cF
