#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte



#include <vector>
#include <string>
#include <memory>
#include <random>
#include <memory>          // ⭐ unique_ptr
#include "ItemBase.h"      // ⭐ ItemBase 정의 + ShopType enum
#include "Item.h"
using namespace std;


enum class MerchantPersonality { Friendly, Grumpy, Sarcastic, Animal };

class Store {
    vector<unique_ptr<ItemBase>> store, masterItems;
    ShopType type;
    string ownerName;
    int day;
    MerchantPersonality personality;
public:
    Store(ShopType t, const string& owner, MerchantPersonality p = MerchantPersonality::Friendly);
    string getOwnerName() const;
    int getDay() const;
    const vector<unique_ptr<ItemBase>>& getStore() const;
    MerchantPersonality getPersonality() const;
    void restock();
    void nextDay();
    bool buyItem(int idx, vector<unique_ptr<ItemBase>>& inv, int& gold);
    void sellItem(unique_ptr<ItemBase>& item, int qty, vector<unique_ptr<ItemBase>>& inv, int& gold);
};
