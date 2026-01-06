#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "Store.h"
#include "Player.h"
#include "Inventory.h"

#include <map>
#include <vector>
#include <string>

class StoreUI {
private:
    Store& store;
    Player& player;
    Inventory& inventory;
    int& gold;

    std::map<MerchantPersonality, std::vector<std::string>> buyLines;
    std::map<MerchantPersonality, std::vector<std::string>> sellLines;
    std::map<MerchantPersonality, std::vector<std::string>> noGoldLines;
    std::map<MerchantPersonality, std::vector<std::string>> newStockLines;

    void merchantSpeak(const std::string& msg);
    std::string randomLine(
        const std::map<MerchantPersonality, std::vector<std::string>>& linesMap);

    int selectInventoryItem();
    int selectSellQuantity(int maxQty);

public:
    StoreUI(Store& s, Player& p, Inventory& inv, int& g);
    void run();
};
