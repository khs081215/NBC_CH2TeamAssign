#include "Troll.h"
#include <iostream>


// Troll 구현
Troll::Troll(int Playerlevel) : Monster(Playerlevel,"Troll")
{

}

void Troll::display()
{
    char print_temp[256];
    FILE* fp;
    errno_t err = fopen_s(&fp, "Troll.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
}
