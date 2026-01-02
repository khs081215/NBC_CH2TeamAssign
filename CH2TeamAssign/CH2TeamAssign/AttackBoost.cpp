//AttackBoost.cpp 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <string>
#include "AttackBoost.h"
#include "Player.h"

using namespace std;

string AttackBoost::getName() const {
    return name;
}

int AttackBoost::GetPrice() const {
    return price;
}

void AttackBoost::Use(Player& player) {
    player.IncreaseATK(AttackIncrease);
}