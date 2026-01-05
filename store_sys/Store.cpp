//Store.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "Store.h"
#include "MasterItems.h"
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

int STORE_DISPLAY_COUNT = 10;

Store::Store(ShopType t, const string& owner, MerchantPersonality p)
    : type(t), ownerName(owner), personality(p), day(1) {
    masterItems = getMasterItems();
    restock();
}

string Store::getOwnerName() const { return ownerName; }
int Store::getDay() const { return day; }
const Inventory& Store::getStore() const { return store; }
MerchantPersonality Store::getPersonality() const { return personality; }

void Store::restock() {
    store.clear();
    random_device rd;
    mt19937 gen(rd());
    vector<ItemBase*> candidates;

    for (auto& i : masterItems)
        if (i->getCategory() == type || type == ShopType::General)
            candidates.push_back(i.get());

    shuffle(candidates.begin(), candidates.end(), gen);

    for (int i = 0; i < min(STORE_DISPLAY_COUNT, (int)candidates.size()); i++) {
        auto copy = candidates[i]->clone();
        copy->addQuantity(gen() % 4);
        store.AddItem(move(copy));
    }
}

void Store::nextDay() { day++; restock(); }

bool Store::buyItem(int idx, Inventory& inv, int& gold) {
    if (idx < 0 || idx >= (int)store.size()) return false;
    if (gold < store[idx]->GetPrice()) return false;

    gold -= store[idx]->GetPrice();

    for (auto& i : inv)
        if (i->getName() == store[idx]->getName()) {
            i->addQuantity(1);
            store.erase(store.begin() + idx);
            return true;
        }

    inv.AddItem(store[idx]->clone());
    store.erase(store.begin() + idx);
    return true;
}

void Store::sellItem(ItemBase* item, int qty, Inventory& inv, int& gold) {
    if (!item || qty <= 0) return;

    gold += (item->GetPrice() * 60 / 100) * qty;
    item->removeQuantity(qty);

    if (item->getQuantity() <= 0) {
        for (int i = 0; i < inv.size(); ++i) {
            if (inv[i]->getName() == item->getName()) {
                inv.erase(i);
                break;
            }
        }
    }
}

