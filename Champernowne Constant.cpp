class champernowneConstant
{
public:
	long long int maxDigit;
	vector<long long int> totalDigit;
	champernowneConstant(long long int _maxDigit)
	{
		maxDigit = _maxDigit;
		totalDigit = vector<long long int> (maxDigit + 1);
		long long int i = 0, curr = 1;
		totalDigit[i++] = 0;
		while (i <= maxDigit)
		{
			totalDigit[i] = (long long int)(i * curr);
			totalDigit[i] *= 9;
			i++;
			curr *= 10;
		}
	}
	long long int getKthDigit(long long int  k)
	{
		long long int digit = 1, start = 1;
		while (k >= totalDigit[digit])
		{
			k -= totalDigit[digit++];
			start *= 10;
		}
		start--;
		long long int covered = k / digit;
		long long int rem = k % digit;
		long long int num = start + covered;
		if (rem != 0)
		{
			num++;
			long long int divTime = digit - rem + 1;
			while (divTime--)
			{
				rem = num % 10;
				num /= 10;
			}
		}
		else
		{
			rem = num % 10;
		}
		return rem;
	}
};
