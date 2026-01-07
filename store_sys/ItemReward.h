//ItemReward.h
#pragma once
#include "QuestReward.h"
#include "ItemBase.h"

class ItemReward : public QuestReward {
    std::unique_ptr<ItemBase> item;

public:
    ItemReward(std::unique_ptr<ItemBase> i)
        : item(std::move(i)) {
    }

    void Give(Inventory& inventory) override {
        inventory.AddItem(std::move(item));
    }
};
