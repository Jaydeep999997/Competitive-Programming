#include<bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long int ll;
typedef pair<int, int> pi;
typedef pair<long long, long long> pll;

#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define int long long   // Make sure to use ll everywhere while commenting this, to avoid overflow
#define sz(v) (int)v.size()
#define inf 2147483647
#define llinf 9223372036854775807
#define all(v) v.begin(),v.end()
#define bp(n) __builtin_popcountll(n)
#define f(i,l,r) for(long long i=l;i<=r;i++)
#define rf(i,r,l) for(long long i=r;i>=l;i--)
#define fast ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }


const int N = 3e5 + 5, mod = 1e9 + 7, bit = 61;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

signed main()
{
	fast;


#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int t = 1;
// 	cin >> t;
	f(tc, 1, t)
	{

	}
	return 0;
}
