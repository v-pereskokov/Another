#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>

void spaces(std::string &sentence, std::size_t differnce)
{
    std::stringstream ss(sentence);
    std::string word;
    int count = 0;
    while (ss >> word)
        ++count;
    while (differnce > 0) {
        std::stringstream ss1(sentence);
        for (int i = 0; i < count - 1; ++i) {
            ss1 >> word;
            auto index = sentence.find(word);
            sentence.insert((index + word.size()), " ");
            --differnce;
            if (differnce == 0)
                break;
        }
    }
}

std::size_t find_max_len(std::fstream &file, std::string &sentence)
{
    std::size_t max = 0;
    while (std::getline(file, sentence)) {
        std::size_t len = sentence.size();
        if (len > max)
            max = len;
    }
    return max;
}

void tabulation(std::fstream &file, std::fstream &file1, std::size_t n = 0)
{
    std::string sentence;
    std::size_t max = find_max_len(file, sentence);
    if (n == 0)
        n = max;
    else if (n < max && n != 0)
        throw std::logic_error("\nN < Max len");
    else
        max = n;
    file.clear();
    file.seekg(0, std::ios::beg);
    bool is_tab = false;
    int i = 0;
    while (std::getline(file, sentence)) {
        if (is_tab)
            sentence.insert(0, "    ");
        if (sentence.empty())
            is_tab = true;
        else
            is_tab = false;
        if (!is_tab) {
            std::size_t len = sentence.size();
            if (len < max) {
                spaces(sentence, max - len);
                file1 << sentence;
                file1 << '\n';
            }
            else if (len == max)
                file1 << sentence;
            is_tab = false;
        }
        else
            file1 << '\n';
    }
}