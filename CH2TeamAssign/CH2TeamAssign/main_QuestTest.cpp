#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <iostream>
#include <conio.h>
#include <memory>

#include "QuestManager.h"
#include "QuestFactory.h"
#include "QuestUI.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemBase.h"

using namespace std;

QuestManager gQuestManager;
Player gPlayer("플레이어");
Inventory gInventory;

void DrawMainUI() {
    system("cls");
    cout << "I: 인벤토리 | Q: 퀘스트 | K: slay monster | ESC: 종료\n";
}



void RunQuestTest()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    bool running = true;
    DrawMainUI();

    while (running) {
        int input = _getch();

        switch (input) {

        case 'i':
        case 'I':
            gInventory.ShowInventoryUI(gPlayer);
            DrawMainUI();
            break;

        case 'q':
        case 'Q':
            OpenQuestUI(gQuestManager);
            DrawMainUI();
            break;

        case 'k':
        case 'K': {
            cout << "슬라임 처치!\n";

            // 1. 이벤트 전달
            gQuestManager.Notify({
                QuestEventType::KillMonster,
                "슬라임",
                1
            });

            // 2. 즉시 완료된 퀘스트 체크
            auto completed = gQuestManager.GetJustCompletedQuests();
            for (auto* q : completed) {
                ShowQuestCompletePopup(q->GetStatusText());
            }

            // 3. 보상 지급
            gInventory.AddItem(
                make_unique<Consumable>(
                    "회복 물약",
                    "HP 50 회복",
                    50,
                    50,
                    ShopType::Herbal
                )
            );

            cout << "회복 물약을 획득했습니다!\n";
            _getch();

            DrawMainUI();
            break;
        }

        case 27:
            running = false;
            break;
        }
    }

    cout << "게임 종료\n";
}

