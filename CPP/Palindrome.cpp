#include <iostream>
#include <string>

bool searchPalindrome(const std::string &string)
{
	auto it1(string.begin()), it2(string.end());
	while (it1 < it2)
	{
		if (*it1++ != *(--it2))
			return false;
	}
	return true;
}

int main()
{
	std::string string;
	while (string != "stop")
	{
		std::getline(std::cin, string);
		if (string == "stop")
			break;
		if (searchPalindrome(string))
			std::cout << "TRUE! \n";
		else
			std::cout << "FALSE! \n";
	}
	system("pause");
	return 0;
}
