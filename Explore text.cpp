#include <iostream>
#include <string>
#include <fstream>
#include <map>

void explore(std::fstream &file)
{
	std::string string, signs = ".,!?;:|{}[]<>~`()*&^%$#@+- ";
	std::map<std::string, size_t> Occurence;
	while (file >> string)
	{
		for (std::string::size_type pos = 0;
		(pos = string.find_first_not_of(signs, pos)) != std::string::npos;)
		{
			auto n = pos;
			pos = string.find_first_of(signs, pos);
			std::string word = string.substr(n, pos == std::string::npos ? pos : pos - n);
			++Occurence[word];
		}
	}
	for (const auto &temp : Occurence)
		std::cout << "Number of < " << temp.first << " > in text is : " << temp.second << std::endl;
}

int main()
{
	std::string fileName;
	std::cin >> fileName;
	std::fstream file(fileName);
	explore(file);
	file.close();
	system("pause");
	return 0;
}
