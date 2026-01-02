#include "AttackBoost.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Store.h"
#include <iostream>

using namespace std;

#include "Slime.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"

int main() {
    srand((unsigned int)time(NULL));
    //슬라임, 고블린, 오크, 트롤 정보 불러오기
    Monster* s = new Slime(playerLevel);
    Monster* g = new Goblin(playerLevel);
    Monster* o = new Orc(playerLevel);
    Monster* t = new Troll(playerLevel);

    s->showInfo();
    g->showInfo();
    o->showInfo();
    t->showInfo();


    delete s; 
    delete g; 
    delete o; 
    delete t;

    return 0;
}