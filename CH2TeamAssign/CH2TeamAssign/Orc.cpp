#include "Orc.h"
#include <iostream>


// Orc 구현
Orc::Orc() : Monster("Orc", 1, 90, 50) {}

void Orc::Shout() {
    std::cout << "오크가 포효합니다!" << std::endl;
}