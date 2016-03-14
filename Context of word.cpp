#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::string> vector;
vector push_word(vector &vector, const std::string &string, size_t i)
{
    std::string signs = ".,!?;|{}[]<>~`()*&^%$#@+-/\\ ";
    for (std::string::size_type pos = 0;
         (pos = string.find_first_not_of(signs, pos)) != std::string::npos;)
    {
        auto n = pos;
        pos = string.find_first_of(signs, pos);
        std::string word = string.substr(n, pos == std::string::npos ? pos : pos - n);
        vector[i] = word;
    }
    return vector;
}

void word_ambit(std::fstream &file, const std::string &word, int n)
{
    if (n > 0)
    {
        std::vector<std::string> local(2 * n + 1);
        std::string string;
        size_t i(0); // Index of word in vector
        size_t k(0); // Number of words in text
        size_t l(0); // Number of print line
        size_t pos(0); // Position in text
        size_t count(0); // Number of matches
        while (file >> string)
        {
            pos += string.length() + 1;
            if (i == n + 1)
            {
                for (size_t j(0); j < n; j++)
                    local[j] = local[j + 1];
                i = n;
            }
            push_word(local, string, i++);
            if (string == word)
            {
                size_t j(0);
                while ((file >> string) && (j++ < n))
                {
                    push_word(local, string, i++);
                    if (file.eof())
                        break;
                }
                std::cout << ++l << ". ";
                for (const auto& temp : local)
                    std::cout << temp << " ";
                std::cout << std::endl;
                file.seekp(pos, std::ios::beg);
                i = 0;
                ++count;
            }
        }
        if (count == 0)
            std::cout << "No match!!" << std::endl;
    }
    else if (n == 0)
        std::cout << word << std::endl;
    else if (n < 0)
        std::cout << "Error!\nNumber of context less than 0!" << std::endl;
}

int main()
{
    std::cout << "File name : ";
    std::string file_name;
    std::cin >> file_name;
    std::fstream file(file_name);
    if (!file.is_open()){
        std::cout << "Error!\n";
        return -1;
    }
    std::cout << "Word : ";
    std::string word;
    std::cin >> word;
    std::cout << "Number of context : ";
    int n;
    std::cin >> n;
    word_ambit(file, word, n);    file.close();
    return 0;
}
