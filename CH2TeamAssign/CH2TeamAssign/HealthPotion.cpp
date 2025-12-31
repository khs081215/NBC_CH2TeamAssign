#include <string>
#include "HealthPotion.h"
#include "Player.h"

using namespace std;

string HealthPotion::getName() const {
    return name;
}

int HealthPotion::getPrice() const {
    return price;
}

void HealthPotion::Use(Player& player) {
    player.RestoreHP(HealthRestore);
}
