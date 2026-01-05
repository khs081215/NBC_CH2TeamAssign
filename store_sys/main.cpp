// main.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <conio.h>

#include "GameManager.h"
#include "ItemAdapter.h"
#include "ItemBase.h"

#include "Monster.h"
#include "Player.h"
#include "Slime.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"

// ===== 네가 만든 시스템 =====
#include "Inventory.h"
#include "Store.h"
#include "StoreUI.h"
#include "QuestManager.h"
#include "QuestUI.h"
#include "UI.h"
#include "Boss.h"

using namespace std;

//한글 출력을 위한 코드
string GetUTFInput() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    wchar_t wbuffer[1024];
    DWORD charactersRead = 0;

    if (!ReadConsoleW(hInput, wbuffer, 1024, &charactersRead, NULL)) {
        return "";
    }

    wstring wstr(wbuffer, charactersRead);
    while (!wstr.empty() && (wstr.back() == L'\r' || wstr.back() == L'\n')) {
        wstr.pop_back();
    }

    if (wstr.empty()) return "";

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
    string utf8Str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &utf8Str[0], size_needed, NULL, NULL);

    return utf8Str;
}

// 전투 코드
bool battle(Player& myPlayer, unique_ptr<Monster>& spawnedMonster, QuestManager& questManager, vector<string>& killedmonster)
{
    myPlayer.ItemAutoUse();
    cout << endl;

    // 몬스터 처치
    if (spawnedMonster->getcurHealth() <= myPlayer.getattack())
    {
        myPlayer.Attack(spawnedMonster.get());

        cout << myPlayer.getplayerName() << "가 "
            << spawnedMonster->GetName() << "을 처치했습니다!\n";

        // ===== 퀘스트 이벤트 =====
        questManager.Notify({
            QuestEventType::KillMonster,
            spawnedMonster->GetName(),
            1
            });

        int getgold = rand() % 11 + 10;
        myPlayer.setexperience(50);
        myPlayer.setgold(myPlayer.getgold() + getgold);

        killedmonster.push_back(
            "LV" + to_string(myPlayer.getlevel()) +
            spawnedMonster->GetName()
        );

        cout << "EXP +50, Gold +" << getgold << endl;

        // ===== 아이템 드랍 =====
        int randitemnum = rand() % 100;

        if (randitemnum < 15)
        {
            myPlayer.GetInventory().AddItem(
                std::make_unique<ItemAdapter>(new HealthPotion())
            );
            cout << "HP 포션 획득!\n";
        }
        else if (randitemnum < 30)
        {
            myPlayer.GetInventory().AddItem(
                std::make_unique<ItemAdapter>(new AttackBoost())
            );
            cout << "공격 포션 획득!\n";
        }

        return true;
    }

    // 플레이어 공격
    myPlayer.Attack(spawnedMonster.get());
    cout << myPlayer.getplayerName() << " 공격 → "
        << spawnedMonster->GetName()
        << " HP: " << spawnedMonster->getcurHealth() << endl;

    // 플레이어 사망 체크
    if (myPlayer.getcurHealth() <= spawnedMonster->GetAttack())
    {
        myPlayer.setcurHealth(0);
        cout << myPlayer.getplayerName() << " 사망! 게임 오버\n";
        return true;
    }

    // 몬스터 공격
    myPlayer.setcurHealth(
        myPlayer.getcurHealth() - spawnedMonster->GetAttack()
    );

    cout << spawnedMonster->GetName()
        << " 공격 → 플레이어 HP: "
        << myPlayer.getcurHealth() << endl << endl;
    return false;
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string characterName;
    unique_ptr<Monster> spawnedMonster;
    vector<string> killedmonster;

    // ===== 캐릭터 생성 =====
    while (true)
    {
        cout << "캐릭터 이름을 입력하세요\n";
        characterName = GetUTFInput();
            
        if (!characterName.empty()) break;
        cout << "캐릭터 이름은 공백이 될 수 없습니다. 다시 입력해주세요\n";
    }

    Player myPlayer(characterName);

    cout << "캐릭터 " << characterName
        << " 생성 완료! 레벨: " << myPlayer.getlevel()
        << ", 체력: " << myPlayer.getcurHealth()
        << ", 공격력: " << myPlayer.getattack() << endl << endl;

    srand((unsigned int)time(nullptr));

    // ==============================
    //  상점 / 퀘스트 시스템 초기화
    // ==============================
    Store store(ShopType::General, "상인", MerchantPersonality::Friendly);

    QuestManager questManager;
    questManager.SetInventory(&myPlayer.GetInventory());
    questManager.SetPopupHandler(ShowQuestCompletePopup);

    DrawMainUI();

    // ===== 메인 게임 루프 =====
    while (myPlayer.getlevel() < 10)
    {
        // ===== 몬스터 생성 =====
        switch (rand() % 4)
        {
        case 0: spawnedMonster = make_unique<Goblin>(myPlayer.getlevel()); break;
        case 1: spawnedMonster = make_unique<Orc>(myPlayer.getlevel()); break;
        case 2: spawnedMonster = make_unique<Troll>(myPlayer.getlevel()); break;
        case 3: spawnedMonster = make_unique<Slime>(myPlayer.getlevel()); break;
        }
        spawnedMonster->display();
        spawnedMonster->showInfo();

        // ===== 전투 루프 =====
        while (true)
        {
            if (battle(myPlayer, spawnedMonster, questManager, killedmonster)) break;
        }
        spawnedMonster.reset();
        if (myPlayer.getcurHealth() == 0) break;

        // ===== 전투 후 메뉴 =====
        bool nextBattle = false;

        while (!nextBattle)
        {
            cout << "\n===== 전투 후 메뉴 =====\n";
            cout << "I: 인벤토리 | Q: 퀘스트 | S: 상점 | P: 상태 | N: 다음 전투\n";
            cout << "선택: ";

            char cmd;
            cin >> cmd;
            cmd = toupper(cmd);

            system("cls");

            switch (cmd)
            {
            case 'I':
                myPlayer.GetInventory().ShowInventoryUI(myPlayer);
                break;

            case 'Q':
                OpenQuestUI(questManager);
                break;

            case 'S':
            {
                StoreUI ui(
                    store,
                    myPlayer,
                    myPlayer.GetInventory(),
                    myPlayer.getGoldRef()
                );
                ui.run();
                DrawMainUI();
                break;
            }

            case 'P':
                myPlayer.PrintStatus();
                break;

            case 'N':
                nextBattle = true;
                break;

            default:
                cout << "잘못된 입력입니다.\n";
                break;
            }
        }

    }

    // ===== 보스 몬스터 =====
    if (myPlayer.getlevel() == 10)
    {
        spawnedMonster = make_unique<Boss>(myPlayer.getlevel());
        spawnedMonster->display();
        spawnedMonster->showInfo();

        while (true)
        {
            if (battle(myPlayer, spawnedMonster, questManager, killedmonster)) break;
        }
        if (myPlayer.getcurHealth() != 0)
        {
            cout << "위대한 보스를 물리쳤습니다!!!" << endl;
        }



        cout << "잡은 몬스터: ";
        for (auto& m : killedmonster)
            cout << m << " ";
        cout << endl;
    }

    return 0;
}