#include <string>
#include "HealthPotion.h"
#include "Player.h"

using namespace std;

string HealthPotion::getName() const {
    return "체력 회복 포션";
}

void HealthPotion::Use(Player& player) {
    player.RestoreHP(HealthRestore);
}