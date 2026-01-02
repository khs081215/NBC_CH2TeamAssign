
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "StoreUI.h"
#include "ItemBase.h"
#include <conio.h>       // _getch()
#include <iostream>      // std::cout, std::endl
#include <vector>        // std::vector
#include <map>           // std::map
#include <string>        // std::string
#include <memory>        // std::unique_ptr
#include <random>        // std::random_device, std::mt19937, std::uniform_int_distribution

// 이제 using namespace std; 제거

StoreUI::StoreUI(Store& s, Player& p, std::vector<std::unique_ptr<ItemBase>>& inv, int& g)
    : store(s), player(p), inventory(inv), gold(g) {

    buyLines = {
        {MerchantPersonality::Friendly, {"꺅너무감사합니다!","어머나영광이에요!","너무굉장한선택이에요!!!"}},
        {MerchantPersonality::Grumpy, {"결제완료되었습니다.","다음번에도들러주십시오.","좋습니다."}},
        {MerchantPersonality::Sarcastic, {"호그걸골라서어따쓸려고?.","샀으면 빨리 나가라.","뒤에손님 있는거 안보이나?"}},
        {MerchantPersonality::Animal, {"멍멍! 고마워용~","야옹~ 잘쓸개냥!","꿀꿀! 다음에도 또 와랴~"}}
    };

    sellLines = {
        {MerchantPersonality::Friendly, {"너무고마워요~잘쓸게효","정말 이런걸주시면어떡해요~~~~!!!","앞으로도마니마니들러주셔야해요"}},
        {MerchantPersonality::Grumpy, {"판매성공적으로되셨습니다","거래완료되었습니다.","거래완료"}},
        {MerchantPersonality::Sarcastic, {"이거내가싸게사주는거야","쓸만한걸로 좀 가져와라.","끙 이런걸 가져오면 어따쓰겟노?"}},
        {MerchantPersonality::Animal, {"멍멍! 판매완료~","야옹~ 잘 받았개냥!","꿀꿀! 다음에도 또 팔아랴~"}}
    };

    noGoldLines = {
        {MerchantPersonality::Friendly, {"아앗 ㅠㅠ 잔액이 부족해요!","골드 더 들고오실때까지 기다릴게요!!","헉 어쩌죠 ㅠㅠ"}},
        {MerchantPersonality::Grumpy, {"삐빅. 잔액 부족","잔액이 부족합니다.","돈이 모자랍니다."}},
        {MerchantPersonality::Sarcastic, {"돈도 없는게 왜왔노?","결제 오류 뜬다 함봐봐라","우리가 자원봉사단인줄 아냐?!"}},
        {MerchantPersonality::Animal, {"멍멍! 돈이 없개~","야옹~ 금액이 부족하개냥!","꿀꿀! 골드 더 가져와랴~"}}
    };

    newStockLines = {
        {MerchantPersonality::Friendly, {"새물건들이 도착했어요~","업자님의 피와살과땀이 묻어있는 제품들","오늘도 한번 봐주고 가셔용!!"}},
        {MerchantPersonality::Grumpy, {"신재고 등장.","오늘밖에안팝니다","신제품 출현."}},
        {MerchantPersonality::Sarcastic, {"새상품 도착 함 와보이소.","여기 주목 하이소~~~","돈없으면 다음달에 결제 어쩔거노?"}},
        {MerchantPersonality::Animal, {"멍멍! 새물건 도착~","야옹~ 새로운 아이템 왔개냥!","꿀꿀! 오늘도 새 상품 준비됐개~"}}
    };

    merchantSpeak("어서오세요! 천천히 둘러보세요~");
}

void StoreUI::merchantSpeak(const std::string& msg) {
    clearScreen();
    std::cout << store.getOwnerName() << ": ";
    typeText(msg);
    std::cout << "\n(Press any key to continue)";
    (void)_getch();
}

std::string StoreUI::randomLine(const std::map<MerchantPersonality, std::vector<std::string>>& linesMap) {
    auto& lines = linesMap.at(store.getPersonality());
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(lines.size()) - 1);
    return lines[dist(gen)];
}

int StoreUI::selectInventoryItem() {
    if (inventory.empty()) return -1;
    int sel = 0;
    while (true) {
        clearScreen();
        std::cout << "=== INVENTORY (Select Item) ===\n\n";
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (i == sel) std::cout << COLOR_YELLOW << "> ";
            inventory[i]->displayInfo();
            if (inventory[i].get() == player.getEquippedWeapon()) {
                std::cout << " [EQUIPPED]";
            }
            if (i == sel) std::cout << COLOR_RESET;
        }
        std::cout << "\nUP/DOWN | ENTER Select | ESC Cancel\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < static_cast<int>(inventory.size()) - 1) sel++;
        }
        else if (key == KEY_ENTER) return sel;
        else if (key == KEY_ESC) return -1;
    }
}

int StoreUI::selectSellQuantity(int maxQty) {
    int qty = 1;
    while (true) {
        clearScreen();
        std::cout << "Select quantity to sell\n\n";
        std::cout << "Quantity: " << qty << " / " << maxQty << "\n\n";
        std::cout << "UP/DOWN Change | ENTER Confirm | ESC Cancel\n";
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

void StoreUI::run() {
    int sel = 0;
    while (true) {
        clearScreen();
        std::cout << "Gold: " << gold << " G\n";
        std::cout << "=== Day " << store.getDay() << " ===\n\n";
        auto& storeItems = store.getStore();
        for (int i = 0; i < static_cast<int>(storeItems.size()); i++) {
            if (i == sel) std::cout << COLOR_YELLOW << "> ";
            storeItems[i]->displayInfo();
            if (i == sel) std::cout << COLOR_RESET;
        }
        std::cout << "\nUP/DOWN Move | ENTER Buy | S Sell | I Inventory | N Next Day | ESC Exit\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < static_cast<int>(storeItems.size()) - 1) sel++;
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

            clearScreen();
            inventory[idx]->Use(player);
            if (inventory[idx]->getQuantity() <= 0)
                inventory.erase(inventory.begin() + idx);

            std::cout << "\nPress any key...";
            (void)_getch();
        }
        else if (key == 'n' || key == 'N') {
            store.nextDay();
            merchantSpeak(randomLine(newStockLines));
        }
        else if (key == KEY_ESC) break;
    }
}
