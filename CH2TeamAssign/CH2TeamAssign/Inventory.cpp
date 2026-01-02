#include <iostream>
#include <conio.h>
#include "Inventory.h"
#include "ItemBase.h"
#include "Player.h"


using namespace std;

void Inventory::AddItem(std::unique_ptr<ItemBase> item) {
    if (!item) return;

    // 같은 이름 아이템이면 수량만 증가
    for (auto& i : items) {
        if (i->getName() == item->getName()) {
            i->addQuantity(item->getQuantity());
            return;
        }
    }

    items.push_back(std::move(item));
}

void Inventory::ShowInventoryUI(Player& player) const {
    system("cls");

    // ⭐ 중요: 이전 입력 제거
    while (_kbhit()) _getch();

    cout << "=== PLAYER STATUS ===\n";
    cout << "레벨: " << player.getlevel() << "\n";
    cout << "체력: " << player.getcurHealth()
        << " / " << player.getmaxHealth() << "\n";
    cout << "공격력: " << player.getattack() << "\n";
    cout << "골드: " << player.getgold() << "\n";

    cout << "\n=== INVENTORY ===\n";
    if (items.empty()) {
        cout << "인벤토리가 비어 있습니다.\n";
    }
    else {
        for (int i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". ";
            items[i]->displayInfo();
        }
    }

    cout << "\nZ : 뒤로가기\n";

    while (true) {
        char key = _getch();
        if (key == 'z' || key == 'Z')
            break;
    }
}

