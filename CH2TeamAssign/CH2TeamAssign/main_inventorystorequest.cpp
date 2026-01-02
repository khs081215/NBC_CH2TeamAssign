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



void main_test_StoreQuestInventory_Integration()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Player player("Hero");
    int gold = 500;

    // 상점 생성
    Store store(ShopType::General, "상인", MerchantPersonality::Friendly);

    // 퀘스트 매니저
    QuestManager questManager;
    questManager.SetInventory(&player.GetInventory());
    questManager.SetPopupHandler(ShowQuestCompletePopup);

    bool running = true;
    DrawMainUI();

    while (running)
    {
        int input = _getch();

        switch (input)
        {
        case 'i':
        case 'I':
            player.GetInventory().ShowInventoryUI(player);
            DrawMainUI();
            break;

        case 'q':
        case 'Q':
            OpenQuestUI(questManager);
            DrawMainUI();
            break;

        case 's':
        case 'S':
        {
            StoreUI ui(store, player, player.GetInventory(), gold);
            ui.run();
            DrawMainUI();
            break;
        }

        case 'k':
        case 'K':
        {
            cout << "슬라임 처치!\n";

            // 퀘스트 이벤트 전달
            questManager.Notify({
                QuestEventType::KillMonster,
                "슬라임",
                1
            });

            // 퀘스트 완료 확인 & 팝업
            for (auto& q : questManager.GetActiveQuests()) {
                if (q->IsCompleted() && !q->IsRewardGiven()) {
                    ShowQuestCompletePopup(q->GetStatusText());
                    q->GiveReward(player.GetInventory());
                    q->MarkRewardGiven();
                }
            }

            // 드랍 아이템
            auto drop = GetMonsterDrop(store);
            if (drop) {
                player.GetInventory().AddItem(std::move(drop));
                cout << "아이템 드랍됨!\n";
            }

            _getch();
            DrawMainUI();
            break;
        }

        case 27: // ESC
            running = false;
            break;
        }
    }
}


