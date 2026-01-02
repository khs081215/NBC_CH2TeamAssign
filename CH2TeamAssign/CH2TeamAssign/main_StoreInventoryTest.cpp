#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <iostream>
#include <vector>
#include <memory>

#include "Player.h"
#include "Store.h"
#include "StoreUI.h"
#include "ItemBase.h"

using namespace std;

void RunStoreTest()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Player player("Hero");
    player.setgold(3500);

    vector<unique_ptr<ItemBase>> inventory;

    int& gold = player.getGoldRef();

    Store store(ShopType::General, "상점주인");

    StoreUI ui(store, player, inventory, gold);
    ui.run();

    cout << "게임 종료\n";
}
