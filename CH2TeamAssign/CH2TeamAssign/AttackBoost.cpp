#include <string>
#include "AttackBoost.h"
#include "Player.h"

using namespace std;

void AttackBoost::Use(Player& player) {
    player.IncreaseATK(AttackIncrease);
}
