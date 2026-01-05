//QuestUI.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "QuestUI.h"
#include "QuestManager.h"
#include "QuestFactory.h"
#include "QuestDatabase.h"

#include <iostream>
#include <conio.h>

using namespace std;

void OpenQuestUI(QuestManager& questMgr)
{
    int selectedIndex = 0;

    while (true) {
        system("cls");
        cout << "===== QUEST =====\n\n";

        /* =========================
           진행 중인 퀘스트
        ========================= */
        cout << "=== 진행 중인 퀘스트 ===\n";
        const auto& active = questMgr.GetActiveQuests();

        if (active.empty()) {
            cout << "없음\n";
        }
        else {
            for (auto& q : active) {
                cout << "- " << q->GetStatusText() << "\n";
            }
        }

        /* =========================
           수락 가능 퀘스트 수집
        ========================= */
        vector<const QuestData*> availableQuests;

        for (const auto& q : QuestDatabase::GetAllQuests()) {
            if (questMgr.CanAcceptQuest(q)) {
                availableQuests.push_back(&q);
            }
        }

        cout << "\n=== 수락 가능 퀘스트 ===\n";

        if (availableQuests.empty()) {
            cout << "수락 가능한 퀘스트가 없습니다.\n";
            cout << "\nZ : 뒤로가기\n";

            char key = _getch();
            if (key == 'z' || key == 'Z')
                break;

            continue;
        }

        /* =========================
           선택형 UI 출력
        ========================= */
        for (int i = 0; i < availableQuests.size(); ++i) {
            cout << (i == selectedIndex ? " > " : "   ");
            cout << availableQuests[i]->title << "\n";
        }

        cout << "\n↑↓ 선택 | ENTER 수락 | Z 뒤로가기\n";

        /* =========================
           입력 처리
        ========================= */
        int key = _getch();

        // 방향키
        if (key == 224) {
            key = _getch();
            if (key == 72 && selectedIndex > 0) {                
                selectedIndex--;
            }
            else if (key == 80 && selectedIndex < (int)availableQuests.size() - 1) { // ↓
                selectedIndex++;
            }
        }
        // ENTER -> 퀘스트 수락
        else if (key == 13) {
            const QuestData* selected = availableQuests[selectedIndex];

            questMgr.TakeQuest(
                QuestFactory::CreateFromData(*selected),
                selected->id
            );

            cout << "\n[퀘스트를 수락했습니다]\n";
            _getch();
        }
        // 뒤로가기
        else if (key == 'z' || key == 'Z') {
            break;
        }
    }
}

void ShowQuestCompletePopup(const std::string& title)
{
    system("cls");

    cout << "========================\n";
    cout << "   QUEST COMPLETE!\n";
    cout << "------------------------\n";
    cout << " " << title << "\n";
    cout << "========================\n";
    cout << "\n아무 키나 누르세요...\n";

    _getch();
}

