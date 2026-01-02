
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "ItemBase.h"
#include "Player.h"
#include <iostream>  // cout
// using namespace std;  <-- 제거

// Consumable Use
void Consumable::Use(Player& player) {
    player.RestoreHP(restoreAmount);
    removeQuantity(1);
    std::cout << player.getplayerName() << "이(가) " << name
        << " 사용! 체력 +" << restoreAmount << std::endl;
}

// Equipable Use
void Equipable::Use(Player& player) {
    player.Equip(this);
    std::cout << player.getplayerName() << "이(가) " << name
        << " 장착!" << std::endl;
}
