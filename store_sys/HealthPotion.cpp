#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <iostream>
#include "ItemBase.h"
#include "Player.h"
#include "HealthPotion.h"

// cpp에서 구현
void HealthPotion::Use(Player& player) {
    player.RestoreHP(HealthRestore);
    std::cout << "체력 포션 사용! +" << HealthRestore << " HP\n";
}
