#include "AttackBoost.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Store.h"
#include "Slime.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <vector>

using namespace std;

int main()
{
    string characterName;

    //몬스터 변수
    unique_ptr<Monster> spawnedMonster;

    vector<string> killedmonster;


    while (true)
    {
        cout << "캐릭터 이름을 입력하세요\n" ;
        getline(cin,characterName);
        //cin >> characterName;

        //캐릭터이름 공백 체크
        if (characterName.compare("") != 0) break;
        cout << "캐릭터 이름은 공백이 될 수 없습니다. 다시 입력해주세요" << endl;
    }




    //플레이어 생성자
    Player myPlayer(characterName);

    //플레이어가 싱글톤이라면
     //Player* myPlayer=Player::getInstance(characterName);


    cout << "캐릭터 " + characterName + " 생성 완료! 레벨: " << myPlayer.getlevel() << ", 체력: " << myPlayer.getcurHealth() << ", 공격력: " << myPlayer.getattack() << endl;
    cout << endl;

    //랜덤함수 구현
    srand((unsigned int)time(NULL));


    while (myPlayer.getlevel() < 10) {



        //0~3 랜덤하게 해서 각각 Goblin, Orc, Troll, Slime
        //몬스터 동적할당 및 업캐스팅

        switch (rand() % 4) {
        case 0:
            spawnedMonster = make_unique<Goblin>(myPlayer.getlevel());
            break;
        case 1:
            spawnedMonster = make_unique<Orc>(myPlayer.getlevel());
            break;
        case 2:
            spawnedMonster = make_unique<Troll>(myPlayer.getlevel());
            break;
        case 3:
            spawnedMonster = make_unique<Slime>(myPlayer.getlevel());
            break;
        }



        //몬스터와 전투 개시
        //cout << "몬스터 " + spawnedMonster->GetName() + " 등장! 체력: " + spawnedMonster->getcurHealth() + ", 공격력: " + spawnedMonster->getattack();
        spawnedMonster->showInfo();


        //해당 몬스터와의 전투
        while (true)
        {
            
            
            //포션 행동 결정
            myPlayer.ItemAutoUse();

            cout << endl;
            
            //몬스터와 전투
            if (spawnedMonster->getcurHealth() <= myPlayer.getattack())
            {
                myPlayer.Attack(spawnedMonster.get());
                cout << myPlayer.getplayerName() + "가 " + spawnedMonster->GetName() + "을 공격합니다! " + spawnedMonster->GetName() + " 처치!" << endl;
                int getgold = rand() % 11 + 10;
                cout << myPlayer.getplayerName() + "가 50 EXP와 " << getgold << "골드를 획득했습니다.";
                killedmonster.push_back("LV" +to_string(myPlayer.getlevel())+ spawnedMonster->GetName());
                myPlayer.setexperience(50);
                myPlayer.setgold(myPlayer.getgold() + getgold);
                cout << "현재 EXP: " << myPlayer.getexperience() << "/100, 골드: " << myPlayer.getgold() << endl;
                int randitemnum = rand() % 100;
                //아이템 획득
                if (randitemnum < 15)
                {
                    Item* hp=new HealthPotion();
                    myPlayer.AddItem(hp);
                    cout << "\nHP포션 획득\n";
                }
                else if (randitemnum < 30)
                {
                    Item* ab = new AttackBoost();
                    myPlayer.AddItem(ab);
                    cout << "\n공격포션 획득\n";
                }
                
                break;
            }

            myPlayer.Attack(spawnedMonster.get());
            cout << myPlayer.getplayerName() + "가 " + spawnedMonster->GetName() + "을 공격합니다! " + spawnedMonster->GetName() + " 체력: " << spawnedMonster->getcurHealth() << endl;
            cout << endl;


            if (myPlayer.getcurHealth() <= spawnedMonster->GetAttack())
            {
                myPlayer.setcurHealth(0);
                cout << spawnedMonster->GetName() + ".가 " + myPlayer.getplayerName() + "을 공격합니다! " + myPlayer.getplayerName() + " 체력: " << myPlayer.getcurHealth() << "→ 0" << endl;
                cout << myPlayer.getplayerName() + "가 사망했습니다. 게임 오버!" << endl;
                cout << "잡은 몬스터 : ";
                for (int i = 0; i < killedmonster.size(); i++)
                {
                    cout << killedmonster[i] + " ";
                }
                cout << endl;
                break;
            }
            myPlayer.setcurHealth(myPlayer.getcurHealth() - spawnedMonster->GetAttack());
            cout << spawnedMonster->GetName() + "가 " + myPlayer.getplayerName() + "을 공격합니다! " + myPlayer.getplayerName() + " 체력: " << myPlayer.getcurHealth() << endl;

            cout << endl;
        }



        //스마트 포인터 초기화
        spawnedMonster.reset();




        if (myPlayer.getcurHealth() == 0)
        {
            break;
        }


        //캐릭터 상태 확인하는 코드
        string buffer;
        cout << "\n상태를 확인하시겠습니까? (Y/N)";
        cin >> buffer;
        cout << endl;
        if (buffer == "Y") myPlayer.PrintStatus();



        string yesornoString;
        //상점 방문 여부 확인
        while (true)
        {
            cout << "\n상점을 방문하시겠나요?(Y/N): ";

            cin >> yesornoString;
            if (yesornoString.compare("Y") != 0 && yesornoString.compare("N") != 0)
            {
                cout << "다시 입력해주세요";
            }
            else break;
        }
        if (yesornoString.compare("Y") == 0)
        {
            //상점 코드
            /*
            std::vector<City> cities = getCities();
            City& currentCity = cities[0];
            goToStore(currentCity, myPlayer.GetInventory(), myPlayer.getgold());
            */
            cout << "상점에 방문합니다...(개발중)" << endl;
        }

    }
    if (myPlayer.getlevel() == 10) {
        cout << "\n 10레벨 달성!!!" << endl;
        cout << "잡은 몬스터 : ";
        for (int i = 0; i < killedmonster.size(); i++)
        {
            cout << killedmonster[i] + " ";
        }
        cout << endl;
    }
    return 0;
}