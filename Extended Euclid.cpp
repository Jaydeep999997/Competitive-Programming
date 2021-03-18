ll X, Y, gcd;

ll extEuc(ll A, ll B)
{
	if (B == 0)
	{
		gcd = A;
		X = 1;
		Y = 0;
	}
	else
	{
		extEuc(B, A % B);
		ll temp = X;
		X = Y;
		Y = temp - (A / B) * Y;
	}
	return X;
}

ll mInv(ll C, ll m)
{
	ll inv = extEuc(C, m);
	return ((inv % m) + m) % m;
}
