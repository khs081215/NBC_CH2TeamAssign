#include "AttackBoost.h"
#include "Player.h"
#include <iostream>
using namespace std;

void AttackBoost::Use(Player& player) {
    player.IncreaseATK(AttackIncrease);
    cout << GetName() << " 사용! 공격력 +" << AttackIncrease << endl;
}
