#include "Goblin.h"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

// 고블린: 체력 70, 공격력 35, 레벨 10 (예시)
Goblin::Goblin(int playerLevel) : Monster(playerLevel, "Goblin") {}

void Goblin::display()
{
    cout << COLOR_GREEN;
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Goblin.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
    cout << COLOR_RESET;
}