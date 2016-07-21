#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <utility>

typedef std::pair<std::pair<bool, std::size_t>, std::size_t> tripple_BSS;

tripple_BSS find_N(const std::string &request, std::size_t index)
{
    if (index != -1 && isdigit(request[index])) {
        std::string digits = "";
        while (isdigit(request[index]))
            digits += request[index++];
        return {{true, stoi(digits)}, index};
    }
    return {{false, -1}, -1};
}

/*
 * Возвращаемые значения
 * 1. bool - подходит ли N
 * 2. std::size_t - значение N
 * 3. std::size_t - индекс строки request для проверки k элементов
 */
tripple_BSS check_N(const std::string &request)
{
    std::size_t i = -1;
    if (request[0] == '+')
        i = 1;
    else if (isdigit(request[0]))
        i = 0;
    return find_N(request, i);
}

bool is_sign(const char symbol)
{
    return symbol == '-' || symbol == '+' ? true : false;
}

std::pair<std::vector<int>, bool> check_K(const std::string &request, const std::size_t index, const std::size_t N)
{
    std::vector<int> sequence;
    std::string digit = "";
    for (std::size_t i = index; i < request.size(); ++i) {
        if (isdigit(request[i]))
            digit += request[i];
        else if (request[i] == ' ') {
            if (digit != "")
                sequence.push_back(stoi(digit));
            digit = "";
        }
        else
            return {sequence, false};
        if (sequence.size() == N)
            return {sequence, true};
    }
    if (sequence.size() < N)
        return {sequence, false};
    return {sequence, true};
}

std::pair<std::vector<int>, bool> check_request(std::string &request)
{
    std::vector<int> error {0};
    if (!request.empty()) {
        if (request[request.size() - 1] != ' ')
            request += " ";
        auto pack_N = check_N(request);
        if (pack_N.first.first) {
            auto pack_K = check_K(request, pack_N.second, pack_N.first.second);
            if (pack_K.second)
                return {pack_K.first, true};
            else
                return {error, false};
        }
        else
            return {error, false};
    }
    return {error, false};
}

int sequence(const std::vector<int> &target)
{
    std::size_t count_1 = 1;
    int first_1 = target[0];
    std::size_t count_2 = 0;
    int first_2;
    bool flag_count = false;
    for (std::size_t i = 1; i < target.size(); ++i) {
        if (target[i - 1] <= target[i]) {
            if (!flag_count)
                ++count_1;
            else
                ++count_2;
        }
        else {
            if (count_1 >= count_2) {
                first_2 = target[i];
                count_2 = 1;
                flag_count = true;
            }
            else {
                first_1 = target[i];
                count_1 = 1;
                flag_count = false;
            }
        }
    }
    return count_1 >= count_2 ? first_1 : first_2;
}

std::pair<std::size_t, int> find_sequences(std::string &request)
{
    auto checked_request = check_request(request);
    if (checked_request.second) {
        return {checked_request.first.size(), sequence(checked_request.first)};
    }
    return {-1, -1};
}

int main()
{
    std::string request;
    std::getline(std::cin, request);
    auto result = find_sequences(request);
    if (result.first != -1)
        std::cout << result.first << " " << result.second << std::endl;
    else
        std::cout << "[error]" << std::endl;
    return 0;
}
