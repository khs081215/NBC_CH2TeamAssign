#include <string>
#include "AttackBoost.h"
#include "Player.h"

using namespace std;

string AttackBoost::getName() const {
    return "공격력 증가 포션";
}

void AttackBoost::Use(Player& player) {
    player.IncreaseATK(AttackIncrease);
}