//HealthPotion.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <string>
#include "HealthPotion.h"
#include "Player.h"

using namespace std;

string HealthPotion::getName() const {
    return name;
}

int HealthPotion::GetPrice() const {
    return price;
}

void HealthPotion::Use(Player& player) {
    player.RestoreHP(HealthRestore);
}