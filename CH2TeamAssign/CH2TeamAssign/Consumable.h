#pragma once
#include "ItemBase.h"

class Consumable : public ItemBase {
protected:
    int restoreAmount;

public:
    Consumable(
        const std::string& n,
        const std::string& d,
        int p,
        int r,
        ShopType c,
        int q = 1
    )
        : ItemBase(n, d, p, c, q), restoreAmount(r) {
    }

    // ItemBase 요구
    std::string getType() const override {
        return "Consumable";
    }

    std::unique_ptr<ItemBase> clone() const override {
        return std::make_unique<Consumable>(*this);
    }

    // ⭐ 실제 사용 로직 (cpp에서 구현)
    void Use(Player& player) override;
};
