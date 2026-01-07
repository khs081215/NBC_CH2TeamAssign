#include "Slime.h"

#define COLOR_REV_PURPLE "\033[35m"
#define COLOR_RESET "\033[0m"

// 슬라임: 체력 60, 공격력 30, 레벨 5 (예시)
Slime::Slime(int playerLevel) : Monster(playerLevel, "Slime") {}
void Slime::display()
{
    cout << COLOR_REV_PURPLE;
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Slime.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
    cout << COLOR_RESET;
}