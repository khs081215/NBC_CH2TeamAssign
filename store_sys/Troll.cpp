#include "Troll.h"
#include <iostream>

#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// Troll 구현
Troll::Troll(int Playerlevel) : Monster(Playerlevel,"Troll")
{

}

void Troll::display()
{
    cout << COLOR_BLUE;
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Troll.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
    cout << COLOR_RESET;
}
