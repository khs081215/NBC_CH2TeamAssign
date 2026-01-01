#include "AttackBoost.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Store.h"
#include <iostream>

#include "Slime.h"
#include "Goblin.h"
using namespace std;

int main() {
    // 이제 public 생성자를 통해 객체 생성이 가능합니다.
    Monster* s = new Slime();
    Monster* g = new Goblin();

    s->showInfo();
    g->showInfo();

    delete s;
    delete g;

    return 0;
}