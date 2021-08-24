template<typename T>
class segment	// pass argument as (L,R+1) to process the query from L to R
{
public:

	vector<T> st;
	T defVal;
	int n;

	segment() {}

	segment(int _n, T _defVal = T())
	{
		n = _n;
		defVal = _defVal;
		st.resize(2 * n, defVal);
	}

	T merge(T a, T b)
	{
		return (a + b);
	}

	void create()
	{
		for (int i = n - 1; i > 0; i--)
		{
			st[i] = merge(st[i << 1], st[(i << 1) | 1]);
		}
	}

	void update(int idx, T val)
	{
		for (st[idx += n - 1] = val; idx > 1; idx >>= 1)
		{
			st[idx >> 1] = merge(st[min(idx, idx ^ 1)], st[max(idx, idx ^ 1)]);
		}
	}

	T query(int l, int r)
	{
		T ans = defVal, ansl = defVal, ansr = defVal;
		for (l += n - 1, r += n - 1; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1)
			{
				ansl = merge(ansl, st[l++]);
			}
			if (r & 1)
			{
				ansr = merge(st[--r], ansr);
			}
		}
		ans = merge(ansl, ansr);
		return ans;
	}
};
