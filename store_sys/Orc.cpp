#include "Orc.h"
#include <iostream>

#define COLOR_REV_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"

// Orc 구현 체력 90, 공격력 50, 레벨 1 (예시)
Orc::Orc(int PlayerLevel) : Monster(PlayerLevel,"Orc") {}

void Orc::Shout() {
    std::cout << "\n오크가 포효합니다!" << std::endl;
}

void Orc::display()
{
    cout << COLOR_REV_YELLOW;
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Orc.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
    Shout();
    cout << COLOR_RESET;
}
