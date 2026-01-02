#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "Store.h"
#include "Player.h"   // ⭐ 추가
#include "Utils.h"

using namespace std;

class StoreUI {
    Store& store;
    Player& player;   // ⭐ 추가
    vector<unique_ptr<ItemBase>>& inventory;
    int& gold;

    map<MerchantPersonality, vector<string>> buyLines;
    map<MerchantPersonality, vector<string>> sellLines;
    map<MerchantPersonality, vector<string>> noGoldLines;
    map<MerchantPersonality, vector<string>> newStockLines;

    void merchantSpeak(const string& msg);
    string randomLine(const map<MerchantPersonality, vector<string>>& linesMap);
    int selectInventoryItem();
    int selectSellQuantity(int maxQty);

public:
    // ⭐ 생성자 선언을 cpp와 정확히 맞춤
    StoreUI(Store& s, Player& p,
        vector<unique_ptr<ItemBase>>& inv,
        int& g);

    void run();
};
