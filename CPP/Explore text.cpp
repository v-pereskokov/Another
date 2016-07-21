#include <iostream>
#include <string>
#include <fstream>
#include <map>

typedef std::map<std::string, size_t> map;

map search_word(map &map, const std::string &string)
{
    std::string signs = ".,!?;:|{}[]<>~`()*&^%$#@+-/\\ ";
    for (std::string::size_type pos = 0;
         (pos = string.find_first_not_of(signs, pos)) != std::string::npos;)
    {
        auto n = pos;
        pos = string.find_first_of(signs, pos);
        std::string word = string.substr(n, pos == std::string::npos ? pos : pos - n);
        ++map[word];
    }
    return map;
}

void explore(std::fstream &file)
{
    std::string string;
    std::map<std::string, size_t> occurence;
    while (file >> string)
        search_word(occurence, string);
    for (const auto &temp : occurence)
        std::cout << "Number of < " << temp.first << " > in text is : " << temp.second << std::endl;
}

int main()
{
    std::string fileName;
    std::cin >> fileName;
    std::fstream file(fileName);
    explore(file);
    file.close();
    return 0;
}
