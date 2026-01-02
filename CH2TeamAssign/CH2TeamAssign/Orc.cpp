#include "Orc.h"
#include <iostream>


// Orc 구현
Orc::Orc(int Playerlevel) : Monster (player level, "Orc") {}

void Orc::Shout() {
    std::cout << "오크가 포효합니다!" << std::endl;
}