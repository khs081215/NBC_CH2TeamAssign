//HealthPotion.h
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#ifndef HealthPotion_H_
#define HealthPotion_H_
#include <string>
#include "item.h"

class HealthPotion : public Item {
private:
    std::string name = "Health Potion";
    int HealthRestore = 50;
    int price = 10;
public:
    std::string getName() const override;
    int GetPrice() const override;
    void Use(Player& player) override;
};
#endif