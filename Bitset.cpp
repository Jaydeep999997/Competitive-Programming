const int SZ = 2001;

void functions()
{
	bitset<SZ> bit;
	bit.all(); //checks whether all bits are set or not
	bit.any(); //checks whether >= 1 bit is on
	bit.none(); //checks if all bits are off
	bit.count(); //counts no of set bits
	bit.flip(); //flips all bits
	bit.flip(1); //flips 1st bit
	bit.reset(); //resets all bits to 0
	bit.reset(1); //resets 1st bit
	bit.set(); //sets all bits to 1
	bit.set(1); //sets 1st bit to 1
	bit.size(); //return size of bitset
	bit.test(1); //check if 1st bit is on or not
	cout << bit.to_string(); //converts to string
  bit._Find_first(); //Rerutns first set bit starting from left 
  bit._Find_next(idx); // find the first position which is > idx and with the set bit 
  bit.to_ullong(); // Return the converted integer, overflow_error will occur if the value can not be represented in unsigned long long
 
}

Problem0: https://www.codechef.com/problems/CHEFQUE
Solution0: https://pastebin.com/bpX0L7z5

Problem1: https://www.codechef.com/AABH2020/problems/ODTPIC
Solution1: https://pastebin.com/MfWYxN6x

Problem2: https://www.codechef.com/problems/SHAIKHGN
Solution2: https://pastebin.com/jDtSAGKD (Matrix Exp. using bitset)
