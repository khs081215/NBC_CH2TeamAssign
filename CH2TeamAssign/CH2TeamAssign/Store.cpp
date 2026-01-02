
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "Store.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "ItemBase.h"
using namespace std;

int STORE_DISPLAY_COUNT = 10;
Store::Store(ShopType t, const string& owner, MerchantPersonality p)
    : type(t), ownerName(owner), personality(p), day(1) {
    masterItems.push_back(make_unique<Consumable>("kechup", "극심한 HP 회복", 100, 50, ShopType::General));
    masterItems.push_back(make_unique<Consumable>("보리밥", "콩밥은 아직준비되지않음", 40, 10, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("킹크랩", "그리운맛.", 120, 30, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("식물이", "식집사가 애지중지키운 약초", 80, 20, ShopType::Herbal));
    masterItems.push_back(make_unique<Consumable>("사약", "만병치료제", 150, 0, ShopType::Herbal));
    masterItems.push_back(make_unique<Equipable>("포크", "포세이돈의 전설의 삼지창", 500, 10, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("냄비뚜껑", "주방템(방패)", 300, 5, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("4b연필", "미술인시티 최첨단무기", 250, 6, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("강철팬티", "가벼운 방어구.치명타방어", 400, 4, ShopType::Equipment));
    masterItems.push_back(make_unique<Consumable>("허브차", "체력을 천천히 회복", 30, 15, ShopType::Herbal));
    masterItems.push_back(make_unique<Consumable>("사과", "달콤한 사과, HP 5 회복", 10, 5, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("빵", "포만감 회복", 20, 10, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("엘릭서", "HP & MP 완전 회복", 300, 100, ShopType::General));
    masterItems.push_back(make_unique<Equipable>("나무검", "초보용 무기", 100, 2, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("철검", "평범한 검", 200, 5, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("강철갑옷", "방어력 +10", 500, 0, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("마법지팡이", "마법 공격 +8", 450, 8, ShopType::Equipment));
    masterItems.push_back(make_unique<Consumable>("당근", "HP 소량 회복", 5, 2, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("독약", "사용 시 HP 감소", 50, -20, ShopType::Herbal));
    restock();
}

string Store::getOwnerName() const { return ownerName; }
int Store::getDay() const { return day; }
const vector<unique_ptr<ItemBase>>& Store::getStore() const { return store; }
MerchantPersonality Store::getPersonality() const { return personality; }

void Store::restock() {
    store.clear();
    random_device rd; mt19937 gen(rd());
    vector<ItemBase*> candidates;
    for (auto& i : masterItems)
        if (i->getCategory() == type || type == ShopType::General)
            candidates.push_back(i.get());
    shuffle(candidates.begin(), candidates.end(), gen);
    for (int i = 0; i < min(STORE_DISPLAY_COUNT, (int)candidates.size()); i++) {
        auto copy = candidates[i]->clone();
        copy->addQuantity(gen() % 4);
        store.push_back(move(copy));
    }
}

void Store::nextDay() { day++; restock(); }

bool Store::buyItem(int idx, vector<unique_ptr<ItemBase>>& inv, int& gold) {
    if (idx < 0 || idx >= store.size()) return false;
    if (gold < store[idx]->GetPrice()) return false;
    gold -= store[idx]->GetPrice();
    for (auto& i : inv)
        if (i->getName() == store[idx]->getName()) { i->addQuantity(1); store.erase(store.begin() + idx); return true; }
    inv.push_back(store[idx]->clone());
    store.erase(store.begin() + idx);
    return true;
}

void Store::sellItem(unique_ptr<ItemBase>& item, int qty, vector<unique_ptr<ItemBase>>& inv, int& gold) {
    gold += (item->GetPrice() * 60 / 100) * qty;
    item->removeQuantity(qty);
    if (item->getQuantity() == 0)
        inv.erase(remove_if(inv.begin(), inv.end(),
            [&](auto& i) { return i->getName() == item->getName(); }), inv.end());
}
