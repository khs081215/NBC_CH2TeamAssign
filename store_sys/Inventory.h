#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "ItemBase.h"

class Player;

class Inventory {
private:
    std::vector<std::unique_ptr<ItemBase>> items;

public:
    int size() const { return static_cast<int>(items.size()); }
    bool empty() const { return items.empty(); }

    ItemBase* operator[](int index) const {
        return items[index].get();
    }

    auto begin() { return items.begin(); }
    auto end() { return items.end(); }
    auto begin() const { return items.begin(); }
    auto end() const { return items.end(); }

    void clear() { items.clear(); }

    void erase(int index) {
        items.erase(items.begin() + index);
    }

    void erase(std::vector<std::unique_ptr<ItemBase>>::iterator it) {
        items.erase(it);
    }

    // 선언
    void AddItem(std::unique_ptr<ItemBase> item);
    int GetItemCount() const;
    ItemBase* GetItem(int index) const;
    void UseItem(int index, Player& player);
    void ShowInventoryUI(Player& player) const;
};
