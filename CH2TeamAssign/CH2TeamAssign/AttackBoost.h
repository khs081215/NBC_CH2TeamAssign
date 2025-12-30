#pragma once
#ifndef AttackBoost_H_
#define AttackBoost_H_
#include "item.h"

class AttackBoost : public Item {
private:
    int AttackIncrease = 10;
    int price = 20;
public:
    std::string getName() const override;
    int GetPrice() const override;
    void Use(Player& player) override;
};
#endif
