#include <string>
#include "stack.h"
#include "switch.h"
#include <iostream>

int main()
{
    init_switch();
    stack s;
    std::size_t n;
    std::cin >> n;
    std::string enter;
    int v;
    for (std::size_t i = 0; i < n; ++i)
    {
        int value;
        std::cin >> enter;
        switch(cmd_map[enter])
        {
            case add:
                std::cin >> value;
                s.add(value);
                break;
            case get:
                v = s.get();
                break;
            case del:
                s.del();
                break;
        }
    }
    std::cout << v << std::endl;
    return 0;
}