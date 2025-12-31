#pragma once
#ifndef AttackBoost_H_
#define AttackBoost_H_
#include <string>
#include "item.h"

class AttackBoost : public Item {
private:
    std::string name = "공격력 증가 물약";
    int AttackIncrease = 10;
    int price = 20;
public:
    std::string getName() const override;
    int GetPrice() const override;
    void Use(Player& player) override;
};
#endif
