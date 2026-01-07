#include "printonebyone.h"

void printonebyone::print(const std::string& msg)
{
    for (char c : msg) {
        std::cout << c;
        Sleep(5);
    }
}