// Author: https://codeforces.com/profile/neal
// Source: https://codeforces.com/contest/1334/submission/76217102

// User defined complex data type
// This is noticeably faster than std::complex for some reason.

template<typename float_t>
struct myComplex
{
	float_t x, y;

	myComplex<float_t>(float_t _x = 0, float_t _y = 0) : x(_x), y(_y) {}

	float_t real() const { return x; }
	float_t imag() const { return y; }

	void real(float_t _x) { x = _x; }
	void imag(float_t _y) { y = _y; }

	myComplex<float_t>& operator+=(const myComplex<float_t> &other) { x += other.x; y += other.y; return *this; }
	myComplex<float_t>& operator-=(const myComplex<float_t> &other) { x -= other.x; y -= other.y; return *this; }

	myComplex<float_t> operator+(const myComplex<float_t> &other) const { return myComplex<float_t>(*this) += other; }
	myComplex<float_t> operator-(const myComplex<float_t> &other) const { return myComplex<float_t>(*this) -= other; }

	myComplex<float_t> operator*(const myComplex<float_t> &other) const
	{
		return {x * other.x - y * other.y, x * other.y + other.x * y};
	}

	myComplex<float_t> operator*(float_t mult) const
	{
		return {x * mult, y * mult};
	}

	friend myComplex<float_t> conj(const myComplex<float_t> &c)
	{
		return {c.x, -c.y};
	}

	friend ostream& operator<<(ostream & stream, const myComplex<float_t> &c)
	{
		return stream << '(' << c.x << ", " << c.y << ')';
	}
};

template<typename float_t>
myComplex<float_t> getPolar(float_t magnitude, float_t angle)
{
	return {magnitude * cos(angle), magnitude * sin(angle)};
}

namespace FFT
{
using float_t = double;

const float_t ONE = 1;
const float_t PI = acos(-ONE);

vector<myComplex<float_t>> roots = {{0, 0}, {1, 0}};
vector<int> bit_reverse;

bool is_power_of_two(int n)
{
	return (n & (n - 1)) == 0;
}

int round_up_power_two(int n)
{
	while (n & (n - 1))
	{
		n = (n | (n - 1)) + 1;
	}

	return max(n, 1);
}

// Given n (a power of two), finds k such that n == 1 << k.
int get_length(int n)
{
	assert(is_power_of_two(n));
	return __builtin_ctz(n);
}

// Rearranges the indices to be sorted by lowest bit first, then second lowest, etc., rather than highest bit first.
// This makes even-odd div-conquer much easier.
template<typename myComplex_array>
void bit_reorder(int n, myComplex_array &&values)
{
	if ((int) bit_reverse.size() != n)
	{
		bit_reverse.assign(n, 0);
		int length = get_length(n);

		for (int i = 0; i < n; i++)
		{
			bit_reverse[i] = (bit_reverse[i >> 1] >> 1) | ((i & 1) << (length - 1));
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (i < bit_reverse[i])
		{
			swap(values[i], values[bit_reverse[i]]);
		}
	}
}

void prepare_roots(int n)
{
	if ((int) roots.size() >= n)
		return;

	int length = get_length(roots.size());
	roots.resize(n);

// The roots array is set up such that for a given power of two n >= 2, roots[n / 2] through roots[n - 1] are
// the first half of the n-th roots of unity.
	while (1 << length < n)
	{
		float_t min_angle = 2 * PI / (1 << (length + 1));

		for (int i = 0; i < 1 << (length - 1); i++)
		{
			int index = (1 << (length - 1)) + i;
			roots[2 * index] = roots[index];
			roots[2 * index + 1] = getPolar(ONE, min_angle * (2 * i + 1));
		}

		length++;
	}
}

template<typename myComplex_array>
void fft_iterative(int N, myComplex_array &&values)
{
	assert(is_power_of_two(N));
	prepare_roots(N);
	bit_reorder(N, values);

	for (int n = 1; n < N; n *= 2)
	{
		for (int start = 0; start < N; start += 2 * n)
		{
			for (int i = 0; i < n; i++)
			{
				const myComplex<float_t> &even = values[start + i];
				myComplex<float_t> odd = values[start + n + i] * roots[n + i];
				values[start + n + i] = even - odd;
				values[start + i] = even + odd;
			}
		}
	}
}

inline myComplex<float_t> extract(int N, const vector<myComplex<float_t>> &values, int index, int side)
{
	if (side == -1)
	{
// Return the product of 0 and 1.
		int other = (N - index) & (N - 1);
		return (conj(values[other] * values[other]) - values[index] * values[index]) * myComplex<float_t>(0, 0.25);
	}

	int other = (N - index) & (N - 1);
	int sign = side == 0 ? +1 : -1;
	myComplex<float_t> multiplier = side == 0 ? myComplex<float_t>(0.5, 0) : myComplex<float_t>(0, -0.5);
	return multiplier * myComplex<float_t>(values[index].real() + values[other].real() * sign,
	                                       values[index].imag() - values[other].imag() * sign);
}

void invert_fft(int N, vector<myComplex<float_t>> &values)
{
	assert(N >= 2);

	for (int i = 0; i < N; i++)
	{
		values[i] = conj(values[i]) * (ONE / N);
	}

	for (int i = 0; i < N / 2; i++)
	{
		myComplex<float_t> first = values[i] + values[N / 2 + i];
		myComplex<float_t> second = (values[i] - values[N / 2 + i]) * roots[N / 2 + i];
		values[i] = first + second * myComplex<float_t>(0, 1);
	}

	fft_iterative(N / 2, values);

	for (int i = N - 1; i >= 0; i--)
	{
		values[i] = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
	}
}

const int FFT_CUTOFF = 300;
const double SPLIT_CUTOFF = 2e15;
const int SPLIT_BASE = 1 << 15;

template<typename T_out, typename T_in>
vector<T_out> square(const vector<T_in> &input)
{
	if (input.empty())
		return {0};

	int n = input.size();

// Brute force when n is small enough.
	if (n < 1.5 * FFT_CUTOFF)
	{
		vector<T_out> result(2 * n - 1);

		for (int i = 0; i < n; i++)
		{
			result[2 * i] += (T_out) input[i] * input[i];

			for (int j = i + 1; j < n; j++)
			{
				result[i + j] += (T_out) 2 * input[i] * input[j];
			}
		}

		return result;
	}

	int N = round_up_power_two(n);
	assert(N >= 2);
	prepare_roots(2 * N);
	vector<myComplex<float_t>> values(N, 0);

	for (int i = 0; i < n; i += 2)
	{
		values[i / 2] = myComplex<float_t>(input[i], i + 1 < n ? input[i + 1] : 0);
	}

	fft_iterative(N, values);

	for (int i = 0; i <= N / 2; i++)
	{
		int j = (N - i) & (N - 1);
		myComplex<float_t> even = extract(N, values, i, 0);
		myComplex<float_t> odd = extract(N, values, i, 1);
		myComplex<float_t> aux = even * even + odd * odd * roots[N + i] * roots[N + i];
		myComplex<float_t> tmp = even * odd;
		values[i] = aux - myComplex<float_t>(0, 2) * tmp;
		values[j] = conj(aux) - myComplex<float_t>(0, 2) * conj(tmp);
	}

	for (int i = 0; i < N; i++)
	{
		values[i] = conj(values[i]) * (ONE / N);
	}

	fft_iterative(N, values);
	vector<T_out> result(2 * n - 1);

	for (int i = 0; i < (int) result.size(); i++)
	{
		float_t value = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
		result[i] = is_integral<T_out>::value ? round(value) : value;
	}

	return result;
}

template<typename T_out, typename T_in>
vector<T_out> multiply(const vector<T_in> &left, const vector<T_in> &right)
{
	if (left.empty() || right.empty())
		return {0};

	if (left == right)
		return square<T_out>(left);

	int n = left.size();
	int m = right.size();

// Brute force when either n or m is small enough.
	if (min(n, m) < FFT_CUTOFF)
	{
		vector<T_out> result(n + m - 1, 0);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				result[i + j] += (T_out) left[i] * right[j];
			}
		}

		return result;
	}

	int N = round_up_power_two(n + m - 1);
	vector<myComplex<float_t>> values(N, 0);

	for (int i = 0; i < n; i++)
	{
		values[i].real(left[i]);
	}

	for (int i = 0; i < m; i++)
	{
		values[i].imag(right[i]);
	}

	fft_iterative(N, values);

	for (int i = 0; i <= N / 2; i++)
	{
		int j = (N - i) & (N - 1);
		myComplex<float_t> product_i = extract(N, values, i, -1);
		values[i] = product_i;
		values[j] = conj(product_i);
	}

	invert_fft(N, values);
	vector<T_out> result(n + m - 1, 0);

	for (int i = 0; i < (int) result.size(); i++)
	{
		result[i] = is_integral<T_out>::value ? round(values[i].real()) : values[i].real();
	}

	return result;
}

template<typename T>
vector<T> mod_multiply(const vector<T> &left, const vector<T> &right, T mod, bool split)
{
	if (left.empty() || right.empty())
		return {0};

	int n = left.size();
	int m = right.size();

	for (int i = 0; i < n; i++)
	{
		assert(0 <= left[i] && left[i] < mod);
	}

	for (int i = 0; i < m; i++)
	{
		assert(0 <= right[i] && right[i] < mod);
	}

// Brute force when either n or m is small enough. Brute force up to higher values when split = true.
	if (min(n, m) < (split ? 2 : 1) * FFT_CUTOFF)
	{
		const uint64_t U64_BOUND = numeric_limits<uint64_t>::max() - (uint64_t) mod * mod;
		vector<uint64_t> result(n + m - 1, 0);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				result[i + j] += (uint64_t) left[i] * right[j];

				if (result[i + j] > U64_BOUND)
				{
					result[i + j] %= mod;
				}
			}
		}

		for (uint64_t &x : result)
		{
			if (x >= (uint64_t) mod)
			{
				x %= mod;
			}
		}

		return vector<T>(result.begin(), result.end());
	}

	if (!split)
	{
		const vector<uint64_t> &product = multiply<uint64_t>(left, right);
		vector<T> result(n + m - 1, 0);

		for (int i = 0; i < (int) result.size(); i++)
		{
			result[i] = product[i] % mod;
		}

		return result;
	}

	int N = round_up_power_two(n + m - 1);
	vector<myComplex<float_t>> left_fft(N, 0), right_fft(N, 0);

	for (int i = 0; i < n; i++)
	{
		left_fft[i].real(left[i] % SPLIT_BASE);
		left_fft[i].imag(left[i] / SPLIT_BASE);
	}

	fft_iterative(N, left_fft);

	if (left == right)
	{
		copy(left_fft.begin(), left_fft.end(), right_fft.begin());
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			right_fft[i].real(right[i] % SPLIT_BASE);
			right_fft[i].imag(right[i] / SPLIT_BASE);
		}

		fft_iterative(N, right_fft);
	}

	vector<myComplex<float_t>> product(N);
	vector<T> result(n + m - 1, 0);

	for (int exponent = 0; exponent <= 2; exponent++)
	{
		uint64_t multiplier = 1;

		for (int k = 0; k < exponent; k++)
		{
			multiplier = multiplier * SPLIT_BASE % mod;
		}

		fill(product.begin(), product.end(), 0);

		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (x + y == exponent)
				{
					for (int i = 0; i < N; i++)
					{
						product[i] += extract(N, left_fft, i, x) * extract(N, right_fft, i, y);
					}
				}
			}
		}

		invert_fft(N, product);

		for (int i = 0; i < (int) result.size(); i++)
		{
			uint64_t value = round(product[i].real());
			result[i] = (result[i] + value % mod * multiplier) % mod;
		}
	}

	return result;
}

template<typename T>
vector<T> mod_power(const vector<T> &v, int exponent, T mod, bool split = 1)
{
	assert(exponent >= 0);
	vector<T> result = {1};

	if (exponent == 0)
		return result;

	for (int k = 31 - __builtin_clz(exponent); k >= 0; k--)
	{
		result = mod_multiply(result, result, mod, split);

		if (exponent >> k & 1)
		{
			result = mod_multiply(result, v, mod, split);
		}
	}

	return result;
}

template<typename T>
vector<T> power(const vector<T> &v, int exponent, bool split = 1)
{
	assert(exponent >= 0);
	vector<T> result = {1};

	if (exponent == 0)
		return result;

	for (int k = 31 - __builtin_clz(exponent); k >= 0; k--)
	{
		result = multiply<T>(result, result);

		if (exponent >> k & 1)
		{
			result = multiply<T>(result, v);
		}
	}

	return result;
}
}

// Problem1: https://codeforces.com/contest/632/problem/E
// Solution1: https://pastebin.com/ZDAGJGY8

// Problem2: https://codeforces.com/contest/993/problem/E
// Solution2: https://ideone.com/ofsPtl
