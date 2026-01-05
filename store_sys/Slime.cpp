#include "Slime.h"

// 슬라임: 체력 60, 공격력 30, 레벨 5 (예시)
Slime::Slime(int playerLevel) : Monster(playerLevel, "Slime") {}
void Slime::display()
{
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Slime.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
}
