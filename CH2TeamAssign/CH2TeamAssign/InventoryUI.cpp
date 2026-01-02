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
    Inventory& inv = player.GetInventory();   // ✅ 변경

    if (inv.GetItemCount() == 0) {
        cout << "인벤토리가 비어 있습니다.\n";
        system("pause");
        return;
    }

    int selected = 0;

    while (true) {
        system("cls");
        cout << "===== INVENTORY =====\n\n";

        for (int i = 0; i < inv.GetItemCount(); i++) {
            cout << (i == selected ? " > " : "   ");
            cout << inv.GetItem(i)->getName() << "\n";  // ✅
        }

        cout << "\n[↑↓] 선택  [Enter] 사용  [Z] 나가기\n";

        int key = _getch();

        if (key == 224) {
            key = _getch();
            if (key == 72 && selected > 0) selected--;
            else if (key == 80 && selected < inv.GetItemCount() - 1) selected++;
        }
        else if (key == 13) {
            system("cls");
            inv.UseItem(selected, player);    // ✅ Inventory가 처리

            // ⭐ 사용 후 메시지 출력 후 대기
            cout << inv.GetItem(selected)->getName() << " 사용/장착 완료!\n";
            cout << "계속하려면 아무 키나 누르세요...\n";
            _getch();
        }
        else if (key == 'z' || key == 'Z') {
            break;
        }
    }
}

