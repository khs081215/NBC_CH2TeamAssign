#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <vector>
#include <string>
#include <memory>
#include <random>
#include "ItemBase.h"   // <-- contains ShopType
#include "Inventory.h"  // <-- contains Inventory class

enum class MerchantPersonality { Friendly, Grumpy, Sarcastic, Animal };

class Store {
    Inventory store;                 // Use Inventory type here
    std::vector<std::unique_ptr<ItemBase>> masterItems;
    ShopType type;
    std::string ownerName;
    int day;
    MerchantPersonality personality;

public:
    Store(ShopType t, const std::string& owner, MerchantPersonality p = MerchantPersonality::Friendly);

    std::string getOwnerName() const;
    int getDay() const;
    const Inventory& getStore() const;
    MerchantPersonality getPersonality() const;
    void restock();
    void nextDay();

    bool buyItem(int idx, Inventory& inv, int& gold);
    void sellItem(ItemBase* item, int qty, Inventory& inv, int& gold);
};
