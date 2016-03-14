#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::vector<std::string> vector_string;

template<typename IT>
size_t find_value_n(IT begin1, IT end1, IT begin2, IT end2)
{
    size_t count(0);
    if (begin2 == end2)
        return count;
    while (begin1 != end1)
    {
        auto it1 = begin1, it2 = begin2;
        while (*it1++ == *it2++)
        {
            if (it2 == end2)
                ++count;
        }
        begin1++;
    }
    return count;
}

std::string search_word(const std::string &string)
{
    std::string signs = ".,!?;|{}[]<>~`()*&^%$#@+-/\\ ";
    std::string result;
    for (std::string::size_type pos = 0;
         (pos = string.find_first_not_of(signs, pos)) != std::string::npos;)
    {
        auto n = pos;
        pos = string.find_first_of(signs, pos);
        std::string word = string.substr(n, pos == std::string::npos ? pos : pos - n);
        result = word;
    }
    return result;
}

void word_ambit(std::fstream &file, std::string &word, int n)
{
    if (n < 0)
    {
        std::cout << "Error!\nNumber of word context is less than 0!\nTry again!" << std::endl;
        return;
    }
    std::string string; // String of the text
    size_t match(0); // Number of word in the text
    size_t line(0); // Number of lines
    size_t i(0); // Number of out lines
    while (file.good())
    {
        std::getline(file, string);
        ++line;
        if (n == 0)
        {
            size_t count(find_value_n(string.begin(), string.end(), word.begin(), word.end()));
            if (count > 1)
            {
                ++match;
                std::cout << ++i << ". ";
                std::cout << word << " \\\\ In " << line << " line. Number of word in line is : " << count << std::endl;
            }
            else if (count == 1)
            {
                ++match;
                std::cout << ++i << ". ";
                std::cout << word << " \\\\ In " << line << " line." << std::endl;
            }
        }
        else if (n > 0)
        {
            vector_string local(2 * n + 1);
            size_t pos(0); // Position in the text
            std::stringstream text(string);
            std::string temp;
            while (text >> temp)
            {
                temp = search_word(temp);
            }
            local.clear();
        }
    }
    if (match == 0)
        std::cout << "No match!" << std::endl;
}

int main()
{
    std::cout << "File name : ";
    std::string file_name;
    std::cin >> file_name;
    std::fstream file(file_name);
    if (!file.is_open()){
        std::cout << "Error!\nFile is not open!\nTry again!" << std::endl;
        return -1;
    }
    std::cout << "Word : ";
    std::string word;
    std::cin >> word;
    std::cout << "Number of word context : ";
    int n;
    std::cin >> n;
    word_ambit(file, word, n);
    file.close();
    return 0;
}
