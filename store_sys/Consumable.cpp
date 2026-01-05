
#include "ItemBase.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Consumable::Use(Player& player) {
    player.RestoreHP(restoreAmount);
    removeQuantity(1);
    cout << player.getplayerName() << "이(가) " << getName() << " 사용! 체력 +" << restoreAmount << endl;
}
