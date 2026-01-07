#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte   // Windows SDK의 byte typedef 제거

#include <vector>
#include <string>
#include "Store.h"
#include "ItemBase.h"
#include "Inventory.h"
using namespace std;

struct City {
    string name, description;
    vector<pair<string, ShopType>> stores;
};

int selectStore(const City& city);
MerchantPersonality choosePersonality();


void goToStore(
    const City& currentCity,
    Player& player,
    Inventory& inventory,
    int& gold
);

