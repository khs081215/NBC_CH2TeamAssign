#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "InventoryUI.h"
#include "Player.h"
#include "ItemBase.h"

#include <iostream>
#include <conio.h>

using namespace std;

void OpenInventory(Player& player) {
    const auto& inv = player.getInventory();

    if (inv.empty()) {
        cout << "인벤토리가 비어 있습니다.\n";
        system("pause");
        return;
    }

    int selected = 0;

    while (true) {
        system("cls");
        cout << "===== INVENTORY =====\n\n";

        for (int i = 0; i < inv.size(); i++) {
            cout << (i == selected ? " > " : "   ");
            cout << inv[i]->getName() << "\n";
        }

        cout << "\n[↑↓] 선택  [Enter] 사용  [ESC] 나가기\n";

        int key = _getch();

        if (key == 224) {
            key = _getch();
            if (key == 72 && selected > 0) selected--;
            else if (key == 80 && selected < inv.size() - 1) selected++;
        }
        else if (key == 13) {
            system("cls");
            player.UseItem(selected);
            system("pause");
        }
        else if (key == 'z' || key == 'Z') {
            break;
        }
    }
}
