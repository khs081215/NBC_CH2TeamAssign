#pragma once
#ifndef HealthPotion_H_
#define HealthPotion_H_
#include <string>
#include "item.h"

class HealthPotion : public Item {
private:
    std::string name = "체력 물약";
    int HealthRestore = 50;
    int price = 10;
public:
    std::string getName() const override;
    int getPrice() const override;
    void Use(Player& player) override;
};
#endif
