
#include "ItemBase.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Equipable::Use(Player& player) {
    player.Equip(this);
    cout << player.getplayerName() << "이(가) " << getName() << " 장착!" << endl;
}
