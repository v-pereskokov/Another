template<typename T>
bool searchPalindrome(T string)
{
	size_t i(0);
	auto it1 = string.begin(), it2 = string.end();
	while (i++ < string.length() / 2)
	{
		if (*it1++ != *(--it2))
			return false;
	}
	return true;
}
