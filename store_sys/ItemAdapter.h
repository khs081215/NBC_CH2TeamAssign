#pragma once
#include "ItemBase.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <memory>
#include <string>

class ItemAdapter : public ItemBase {
private:
    Item* originalItem; // 변수 이름 변경

public:
    explicit ItemAdapter(Item* item)
        : ItemBase(
            item->GetName(),
            "Original Item",   // 화면 출력용
            item->GetPrice(),
            ShopType::General,
            1
        ),
        originalItem(item)
    {
    }

    ~ItemAdapter() override {
        delete originalItem;
    }

    void Use(Player& player) override {
        originalItem->Use(player);
    }

    ItemType GetItemType() const override {
        return originalItem->GetItemType();
    }

    std::string getType() const override {
        return "OriginalItem"; // 화면에 출력될 타입
    }

    std::unique_ptr<ItemBase> clone() const override {
        if (originalItem->GetItemType() == ItemType::HealthPotion) {
            return std::make_unique<ItemAdapter>(new HealthPotion());
        }
        if (originalItem->GetItemType() == ItemType::AttackPotion) {
            return std::make_unique<ItemAdapter>(new AttackBoost());
        }
        return nullptr;
    }
};
