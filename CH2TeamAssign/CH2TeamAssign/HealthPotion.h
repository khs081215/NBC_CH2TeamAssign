#pragma once
#ifndef HealthPotion_H_
#define HealthPotion_H_
#include "item.h"
#include <string>

class HealthPotion : public Item {
private:
    int HealthRestore = 50;
public:
    HealthPotion() {
        name = "체력 포션";
        type = ItemType::HealthPotion;
        price = 10;
    }
    void Use(Player& player) override;
};
#endif
