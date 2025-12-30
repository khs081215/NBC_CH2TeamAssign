#pragma once
#ifndef AttackBoost_H_
#define AttackBoost_H_
#include "item.h"

class AttackBoost : public Item {
private:
    int AttackIncrease = 10;
public:
    std::string getName() const override;
    void Use(Player& player) override;
};

#endif


