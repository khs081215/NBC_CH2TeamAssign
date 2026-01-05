//inventory.cpp
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

// ===== 안전하게 아이템 사용 =====
void Inventory::UseItem(int index, Player& player) {
    if (index < 0 || index >= GetItemCount()) return;

    ItemBase* item = GetItem(index);
    if (!item) return;

    item->Use(player);            // 사용
    item->removeQuantity(1);      // 수량 감소

    // 아이템이 1개 남아서 사용 후 0이 되면 삭제
    if (item->getQuantity() <= 0) {
        items.erase(items.begin() + index);
        if (items.empty()) {
            cout << "\n인벤토리가 비었습니다.\n";
        }
    }
}



// ===== 안전한 UI =====
void Inventory::ShowInventoryUI(Player& player) const {
    system("cls");

    cout << "=== PLAYER STATUS ===\n";
    cout << "레벨: " << player.getlevel() << "\n";
    cout << "체력: " << player.getcurHealth() << " / " << player.getmaxHealth() << "\n";
    cout << "공격력: " << player.getattack() << "\n";
    cout << "골드: " << player.getgold() << "\n";

    cout << "\n=== INVENTORY ===\n";

    if (items.empty()) {
        cout << "인벤토리가 비어 있습니다.\n";
        return;
    }

    for (int i = 0; i < GetItemCount(); ++i) {
        cout << i + 1 << ". ";
        items[i]->displayInfo();
    }

    cout << "\nZ : 뒤로가기\n";

    while (true) {
        char key = _getch();

        // 뒤로가기
        if (key == 'z' || key == 'Z')
            break;

        // 숫자 키 입력만 처리
        if (key >= '1' && key <= '0' + GetItemCount()) {
            int choice = key - '1';

            // ⭐ 아이템 이름 미리 저장
            std::string itemName = items[choice]->getName();

            // 아이템 사용
            const_cast<Inventory*>(this)->UseItem(choice, player);

            // 메시지 출력
            system("cls");
            cout << itemName << " 사용 완료!\n";
            cout << "계속하려면 아무 키나 누르세요...\n";
            _getch();
            break; // 사용 후 바로 UI 종료
        }

        // 그 외 키는 무시 (잘못된 입력 메시지 제거)
    }
}


