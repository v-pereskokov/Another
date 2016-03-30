#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::vector<std::string> vector_string;

template<typename IT>
std::size_t find_value_n(IT begin1, IT end1, IT begin2, IT end2)
{
    std::size_t count = 0;
    if (begin2 == end2)
        return count;
    while (begin1++ != end1)
    {
        auto it1 = begin1, it2 = begin2;
        while (*it1++ == *it2++)
        {
            if (it2 == end2)
                ++count;
        }
    }
    return count;
}

vector_string move(vector_string &vector, size_t n)
{
    for (std::size_t i = 0; i < n; i++)
        vector[i] = vector[i + 1];
    return vector;
}

void context(std::fstream &file, std::string &word, int n)
{
    if (n < 0)
    {
        std::cout << "Error!\nNumber of word context is less than 0!\nTry again!" << std::endl;
        return;
    }
    std::string string; // String of the text
    std::size_t pos_file = 0; // Position of line in the text
    std::size_t match = 0; // Number of word in the text
    std::size_t line = 0; // Number of lines
    std::size_t i = 0; // Number of out lines
    if (n == 0)
    {
        while (std::getline(file, string))
        {
            ++line;
            size_t count = find_value_n(string.begin(), string.end(), word.begin(), word.end());
            if (count > 1)
            {
                ++match;
                std::cout << ++i << ". ";
                std::cout << word << " // In " << line << " line. Number of word in line is : " << count << std::endl;
            }
            else if (count == 1)
            {
                ++match;
                std::cout << ++i << ". ";
                std::cout << word << " // In " << line << " line." << std::endl;
            }
        }
    }
    else if (n > 0)
    {
        vector_string local(2 * n + 1);
        std::size_t j = 0; // Index of words in vector(n > 0)
        while (file >> string)
        {
            pos_file += string.length() + 1;
            if (j == n + 1)
            {
                move(local, n);
                j = n;
            }
            local[j++] = string;
            if (string == word)
            {
                ++match;
                std::size_t k = 0;
                while ((file >> string) && (k++ < n))
                    local[k + n] = string;
                std::cout << ++i << ". ";
                for (const auto &c : local)
                    std::cout << c << " ";
                std::cout << std::endl;
                file.seekp(pos_file, std::ios::beg);
            }
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
    std::cout << "Number of words context : ";
    int n;
    std::cin >> n;
    context(file, word, n);
    file.close();
    return 0;
}
