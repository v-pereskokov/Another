#include <iostream>
#include <string>

template<typename T>
bool searchPalindrome(T string)
{
	auto it1(string.begin()), it2(string.end());
	if (it1 == it2)
		return false;
	--it2;
	while (it1 != it2)
	{
		if (*it1 != *(it2))
			return false;
		++it1;
		if (it1 == it2)
			break;
		--it2;
		if (it1 == it2)
			break;
	}
	return true;
}

int main()
{
	std::string string;
	while (string != "stop")
	{
		if (string == "stop")
			break;
		std::getline(std::cin, string);
		if (searchPalindrome(string))
			std::cout << "TRUE! \n";
		else
			std::cout << "FALSE! \n";
	}
	system("pause");
	return 0;
}
