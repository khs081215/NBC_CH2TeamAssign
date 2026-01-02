#include "Inventory.h"
#include "ItemBase.h"
#include "Player.h"

#include <iostream>
#include <conio.h>

using namespace std;

void Inventory::AddItem(std::unique_ptr<ItemBase> item) {
    if (!item) return;

    for (auto& i : items) {
        if (i->getName() == item->getName()) {
            i->addQuantity(item->getQuantity());
            return;
        }
    }
    items.push_back(std::move(item));
}

int Inventory::GetItemCount() const {
    return static_cast<int>(items.size());
}

ItemBase* Inventory::GetItem(int index) const {
    if (index < 0 || index >= GetItemCount())
        return nullptr;
    return items[index].get();
}

void Inventory::UseItem(int index, Player& player) {
    ItemBase* item = GetItem(index);
    if (!item) return;

    item->Use(player);
    item->removeQuantity(1);

    if (item->getQuantity() <= 0) {
        items.erase(items.begin() + index);
    }
}

void Inventory::ShowInventoryUI(Player& player) const {
    system("cls");

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
        for (int i = 0; i < GetItemCount(); ++i) {
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
