#include <string>
#include "HealthPotion.h"
#include "Player.h"

using namespace std;

void HealthPotion::Use(Player& player) {
    player.HealthRestore(HealthRestore);
}
