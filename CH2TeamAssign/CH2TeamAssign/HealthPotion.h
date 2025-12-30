#pragma once
#ifndef HealthPotion_H_
#define HealthPotion_H_
#include "item.h"

class HealthPotion : public Item {
private:
    int HealthRestore = 50;
    int price = 10;
public:
    std::string getName() const override;
    int GetPrice() const override;
    void Use(Player& player) override;
};
#endif
