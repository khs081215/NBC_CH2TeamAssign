
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>

#include "City.h"
#include "StoreUI.h"
#include "Utils.h"
#include "ItemBase.h"
#include "Player.h"


using namespace std;

// 도시 선택 UI
int selectStore(const City& city) {
    int sel = 0;
    while (true) {
        clearScreen();
        cout << "=== " << city.name << " ===\n";
        cout << city.description << "\n\n";
        for (int i = 0; i < city.stores.size(); i++) {
            if (i == sel) cout << COLOR_YELLOW << "> ";
            cout << city.stores[i].first << endl;
            if (i == sel) cout << COLOR_RESET;
        }
        cout << "\nENTER Enter Store | ESC Back\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < city.stores.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) return sel;
        else if (key == KEY_ESC) return -1;
    }
}

// 상점 주인 성격 랜덤 선택
MerchantPersonality choosePersonality() {
    int r = rand() % 100;
    if (r < 50) return MerchantPersonality::Friendly;
    else if (r < 70) return MerchantPersonality::Sarcastic;
    else if (r < 90) return MerchantPersonality::Animal;
    else return MerchantPersonality::Grumpy;
}

// 상점 접근 함수
void goToStore(
    const City& currentCity,
    Player& player,
    Inventory& inventory,
    int& gold)

{
    while (true) {
        int storeIdx = selectStore(currentCity);
        if (storeIdx == -1) break;

        // 상점 주인 이름 추출 (첫 ' 문자 전까지)
        string owner = currentCity.stores[storeIdx].first.substr(
            0, currentCity.stores[storeIdx].first.find('\''));

        MerchantPersonality p = choosePersonality();
        Store store(currentCity.stores[storeIdx].second, owner, p);
        StoreUI ui(store, player, player.GetInventory(), player.getGoldRef());
        ui.run();
        break;
    }
}
