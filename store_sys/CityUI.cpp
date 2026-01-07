// CityUI.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <vector>
#include <iostream>
#include <conio.h>

#include "CityUI.h"
#include "City.h"
#include "Utils.h"

int selectCity(const std::vector<City>& cities, int currentCityIndex)
{
    int sel = currentCityIndex;

    while (true)
    {
        clearScreen();
        std::cout << "=== 이동할 도시 선택 ===\n\n";

        for (int i = 0; i < cities.size(); ++i)
        {
            if (i == sel) std::cout << COLOR_YELLOW << "> ";
            std::cout << cities[i].name << "\n";
            if (i == sel) std::cout << COLOR_RESET;
        }

        std::cout << "\nENTER 이동 | ESC 취소\n";

        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < cities.size() - 1) sel++;
        }
        else if (key == KEY_ENTER)
            return sel;
        else if (key == KEY_ESC)
            return currentCityIndex;
    }
}
