#pragma once
#ifndef HealthPotion_H_
#define HealthPotion_H_
#include "item.h"

class HealthPotion : public Item {
private:
    int HealthRestore = 50;
public:
    std::string getName() const override;
    void Use(Player& player) override;
};
#endif


