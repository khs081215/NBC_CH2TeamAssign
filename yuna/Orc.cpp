#include "Orc.h"
#include <iostream>


// Orc 구현 체력 90, 공격력 50, 레벨 1 (예시)
Orc::Orc(int playerLevel) : Monster(playerLevel,"Orc") {}

void Orc::Shout() {
    std::cout << "오크가 포효합니다!" << std::endl;
}
