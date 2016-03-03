template <typename T>
void swap(T &a, T &b)
{
	T c(a);
	a = b;
	b = c;
}

template <typename T>
void rotate(T begin, T end, int k)
{
	int difference(end - begin);
	if (k % difference != 0)
	{
		T first, now;
		if (k > 0)
		{
			first = end - (k % difference);
			now = end - (k % difference);
		}
		else if (k < 0)
		{
			first = begin + (abs(k) % difference);
			now = begin + (abs(k) % difference);
		}
		while (begin != now)
		{
			swap(*begin++, *now++);
			if (now == end)
				now = first;
			else if (begin == first)
				first = now;
		}
	}
}

bool searchPalindrome(std::string string)
{
	std::string string1 = string;
	rotate(string1.begin(), string1.end(), 5);
	if (string == string1)
		return true;
	return false;
}