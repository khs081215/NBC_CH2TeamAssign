// InventoryUI.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "InventoryUI.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemBase.h"
#include <iostream>
#include <conio.h>

using namespace std;

void OpenInventory(Player& player) {
    Inventory& inv = player.GetInventory();   //  플레이어 인벤토리 참조

    if (inv.GetItemCount() == 0) {
        cout << "인벤토리가 비어 있습니다.\n";
        system("pause");
        return;
    }

    int selected = 0;

    while (true) {
        system("cls");
        cout << "===== INVENTORY =====\n\n";

        int itemCount = inv.GetItemCount();
        if (itemCount == 0) {
            cout << "인벤토리가 비어 있습니다.\n";
            system("pause");
            break; // 인벤토리 비면 UI 종료
        }

        // 아이템 리스트 표시
        for (int i = 0; i < itemCount; i++) {
            cout << (i == selected ? " > " : "   ");
            ItemBase* item = inv.GetItem(i);
            if (item)
                cout << item->getName() << " x" << item->getQuantity() << "\n";
            else
                cout << "[NULL]\n";
        }

        cout << "\n[↑↓] 선택  [Enter] 사용  [Z] 나가기\n";

        int key = _getch();

        if (key == 224) {  // 화살표 입력
            key = _getch();
            if (key == 72) selected--;         // UP
            else if (key == 80) selected++;    // DOWN

            // 범위 클램프
            if (selected < 0) selected = 0;
            if (selected >= inv.GetItemCount()) selected = inv.GetItemCount() - 1;
        }
        else if (key == 13) {  // Enter → 사용
            ItemBase* item = inv.GetItem(selected);
            if (!item) continue;

            string itemName = item->getName(); // 사용 전 이름 저장
            inv.UseItem(selected, player);     // 아이템 사용 & 삭제 가능

            cout << "\n" << itemName << " 사용/장착 완료!\n";
            cout << "계속하려면 아무 키나 누르세요...\n";
            _getch();

            // 선택 인덱스 조정
            if (selected >= inv.GetItemCount())
                selected = inv.GetItemCount() - 1;
        }
        else if (key == 'z' || key == 'Z') {
            break;
        }
    }
}
