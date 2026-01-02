#pragma once
#include "ItemBase.h"

class Player; // 전방 선언

class Equipable : public ItemBase {
    int attackBoost;

public:
    Equipable(string n, string d, int p, int atk, ShopType c, int q = 1);

    string getType() const override;
    unique_ptr<ItemBase> clone() const override;

    void Use(Player& player) override;

    // ⭐ 필수
    int getAttackBoost() const;
};
