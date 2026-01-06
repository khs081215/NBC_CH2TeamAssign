//StoreUI.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "StoreUI.h"
#include "ItemBase.h"
#include "MerchantLines.h"

#include <conio.h>
#include <iostream>
#include <random>

// ---------------------------
// 키 정의
#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_ENTER 13
#define KEY_ESC   27

// 색상
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET  "\033[0m"

// ---------------------------
// 생성자
StoreUI::StoreUI(Store& s, Player& p, Inventory& inv, int& g)
    : store(s), player(p), inventory(inv), gold(g) {

    buyLines = MerchantLines::buyLines;
    sellLines = MerchantLines::sellLines;
    noGoldLines = MerchantLines::noGoldLines;
    newStockLines = MerchantLines::newStockLines;

    merchantSpeak("어서오세요! 천천히 둘러보세요~");
}

// ---------------------------
// NPC 대사 출력
void StoreUI::merchantSpeak(const std::string& msg) {
    system("cls");
    std::cout << store.getOwnerName() << ": ";

    for (char c : msg) {
        std::cout << c;
        Sleep(20);
    }

    std::cout << "\n(Press any key to continue)";
    _getch();
}

// ---------------------------
// 랜덤 대사
std::string StoreUI::randomLine(
    const std::map<MerchantPersonality, std::vector<std::string>>& linesMap) {

    auto& lines = linesMap.at(store.getPersonality());
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (int)lines.size() - 1);
    return lines[dist(gen)];
}

// ---------------------------
// 인벤토리 아이템 선택
int StoreUI::selectInventoryItem() {
    if (inventory.empty()) return -1;

    int sel = 0;
    while (true) {
        system("cls");
        std::cout << "=== INVENTORY ===\n\n";

        for (int i = 0; i < inventory.size(); i++) {
            if (i == sel) std::cout << COLOR_YELLOW << "> ";
            inventory[i]->displayInfo();

            if (inventory[i] == player.getEquippedWeapon())
                std::cout << " [EQUIPPED]";

            if (i == sel) std::cout << COLOR_RESET;
            std::cout << "\n";
        }

        std::cout << "\nUP/DOWN | ENTER Select | ESC Cancel\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < inventory.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) return sel;
        else if (key == KEY_ESC) return -1;
    }
}

// ---------------------------
// 판매 수량 선택
int StoreUI::selectSellQuantity(int maxQty) {
    int qty = 1;
    while (true) {
        system("cls");
        std::cout << "판매 수량 선택\n\n";
        std::cout << "수량: " << qty << " / " << maxQty << "\n\n";
        std::cout << "UP/DOWN 조절 | ENTER 확인 | ESC 취소\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && qty < maxQty) qty++;
            if (key == KEY_DOWN && qty > 1) qty--;
        }
        else if (key == KEY_ENTER) return qty;
        else if (key == KEY_ESC) return -1;
    }
}

// ---------------------------
// 메인 루프
void StoreUI::run() {
    int sel = 0;

    while (true) {
        system("cls");
        std::cout << "Gold: " << gold << " G\n";
        std::cout << "=== Day " << store.getDay() << " ===\n\n";

        const Inventory& storeInv = store.getStore();

        for (int i = 0; i < storeInv.size(); i++) {
            if (i == sel) std::cout << COLOR_YELLOW << "> ";
            storeInv[i]->displayInfo();
            if (i == sel) std::cout << COLOR_RESET;
            std::cout << "\n";
        }

        std::cout << "\nUP/DOWN 이동 | ENTER 구매 | S 판매 | I 인벤토리(사용,장착) | N 다음날 | ESC 종료\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < storeInv.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) {
            if (store.buyItem(sel, inventory, gold))
                merchantSpeak(randomLine(buyLines));
            else
                merchantSpeak(randomLine(noGoldLines));
        }
        else if (key == 's' || key == 'S') {
            int idx = selectInventoryItem();
            if (idx == -1) continue;

            int maxQty = inventory[idx]->getQuantity();
            int qty = selectSellQuantity(maxQty);
            if (qty == -1) continue;

            store.sellItem(inventory[idx], qty, inventory, gold);
            merchantSpeak(randomLine(sellLines));
        }
        else if (key == 'i' || key == 'I') {
            int idx = selectInventoryItem();
            if (idx == -1) continue;

            //  사용 전 아이템 이름 미리 저장
            std::string itemName = inventory[idx]->getName();

            // 아이템 사용 (UseItem 내부에서 삭제될 수 있음)
            inventory.UseItem(idx, player);

            //  erase 후 벡터 접근 금지, 미리 저장한 이름으로 출력
            system("cls");
            std::cout << itemName << " 사용/장착 완료!\n";
            std::cout << "계속하려면 아무 키나 누르세요...\n";
            _getch();

            // 선택 인덱스 재조정: 인벤토리가 비었으면 선택 0, 없으면 마지막 아이템
            if (inventory.empty())
                sel = 0;
            else if (sel >= inventory.size())
                sel = inventory.size() - 1;
        }


        else if (key == 'n' || key == 'N') {
            store.nextDay();
            merchantSpeak(randomLine(newStockLines));
        }
        else if (key == KEY_ESC) {
            break;
        }
    }
}
