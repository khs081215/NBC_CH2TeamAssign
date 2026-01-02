#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "ItemBase.h"
#include "Player.h"

class Inventory {
private:
    std::vector<std::unique_ptr<ItemBase>> items;

public:
    Inventory() = default;

    // Add / Remove items
    void AddItem(std::unique_ptr<ItemBase> item);
    void RemoveItem(int index);

    // Use item
    void UseItem(int index, Player& player);

    // Getter
    ItemBase* GetItem(int index) const;
    int GetItemCount() const;

    // UI
    void ShowInventoryUI(Player& player) const;
};
