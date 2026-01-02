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
    //슬라임, 고블린 정보 불러오기
    Monster* s = new Slime();
    Monster* g = new Goblin();
    Monster* o = new Orc();
    Monster* t = new Troll();

    s->showInfo();
    g->showInfo();
    o->showInfo();
    t->showInfo();


    delete s;
    delete g;

    return 0;
}