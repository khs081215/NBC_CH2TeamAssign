//AttackBoost.H 
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#ifndef AttackBoost_H_
#define AttackBoost_H_
#include <string>
#include "item.h"

class AttackBoost : public Item {
private:
    std::string name = "Attack Boost Potion";
    int AttackIncrease = 10;
    int price = 20;
public:
    std::string getName() const override;
    int GetPrice() const override;
    void Use(Player& player) override;
};
#endif