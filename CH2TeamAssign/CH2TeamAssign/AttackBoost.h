#pragma once
#ifndef AttackBoost_H_
#define AttackBoost_H_
#include "item.h"
#include <string>

class AttackBoost : public Item {
private:
    int AttackIncrease = 10;
public:
    AttackBoost() {
        name = "공격력 포션";
        type = ItemType::AttackPotion;
        price = 10;
    }
    void Use(Player& player) override;
};
#endif
