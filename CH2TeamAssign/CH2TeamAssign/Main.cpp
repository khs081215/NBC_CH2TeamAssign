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
    //슬라임, 고블린, 오크, 트롤 정보 불러오기
    Monster* s = new Slime();
    Monster* g = new Goblin();
    Monster* o = new Orc();
    Monster* t = new Troll();

    s->showInfo();
    g->showInfo();
    o->showInfo();
    t->showInfo();


    delete s;
    delete g;
    string characterName;
    int randnum;
    bool ateattackpotion = false;

    //몬스터 변수
    unique_ptr<Monster> spawnedMonster;

    vector<string> killedmonster;


    while (true)
    {
        cout << "캐릭터 이름을 입력하세요"<<endl;
        cin >> characterName;

        //캐릭터이름 공백 체크
        if (characterName.compare("") != 0) break;
        cout << "캐릭터 이름은 공백이 될 수 없습니다. 다시 입력해주세요" << endl;
    }
    
    


    //플레이어 생성자
    //Player myPlayer(characterName);

    //플레이어가 싱글톤이라면
     Player* myPlayer=Player::getInstance(characterName);


    cout << "캐릭터 " + characterName + " 생성 완료! 레벨: " + myPlayer.GetLevel() + ", 체력: " + myPlayer.GetHP() + ", 공격력: " + myPlayer.GetAttack()<<endl;
   

    //랜덤함수 구현
    srand((unsigned int)time(NULL));


    while (myPlayer.GetLevel() < 10) {



        //0~3 랜덤하게 해서 각각 Goblin, Orc, Troll, Slime
        //몬스터 동적할당 및 업캐스팅
        
        switch (rand() % 4) {
        case 0:
            spawnedMonster = make_unique<Goblin>(myPlayer.GetLevel());
            break;
        case 1:
            spawnedMonster = make_unique<Orc>(myPlayer.GetLevel());
            break;
        case 2:
            spawnedMonster = make_unique<Troll>(myPlayer.GetLevel());
            break;
        case 3:
            spawnedMonster = make_unique<Slime>(myPlayer.GetLevel());
            break;
        }
        


        //몬스터와 전투 개시
        cout << "몬스터 " + spawnedMonster.GetName() + " 등장! 체력: " + spawnedMonster.GetHP() + ", 공격력: " + spawnedMonster.GetAttack();

        //해당 몬스터와의 전투
        while (true)
        {
            //행동 결정
            //체력이 80% 이하면 공격력 포션을 마신다.
            //체력이 20% 이하면 HP포션을 마신다.
            if (myPlayer.GetHP() < (myPlayer.GetMaxHP() * 0.8))
            {
                //공격력 포션을 마신다.
                ateattackpotion = true;
                myPlayer.SetAttack(myPlayer.GetAttack() + 10);
                //TODO: 포션 제거 코드
            }
            if (myPlayer.GetHP() < (myPlayer.GetMaxHP() * 0.2))
            {
                //HP 포션을 마신다.
                //TODO: 포션 제거 코드
            }

            //몬스터와 전투
            if (spawnedMonster.GetHP() <= myPlayer.GetAttack())
            {
                spawnedMonster.takeDamage(myPlayer.GetAttack());
                cout << myPlayer.GetName() + "가 " + spawnedMonster.GetName() + "을 공격합니다! " + spawnedMonster.GetName() + " 처치!" << endl;
                int getgold = rand() % 11 + 10;
                cout << myPlayer.GetName() + "가 50 EXP와 " << getgold << "골드를 획득했습니다.";
                myPlayer.SetExp(myPlayer.GetExp() + 50);
                myPlayer.SetGold(myPlayer.GetGold() + getgold);
                cout << "현재 EXP: " << myPlayer.GetExp() << "/100, 골드: " << myPlayer.GetGold() << endl;
                int randitemnum = rand() % 10;
                if (randitemnum < 3)
                {
                    //TODO: 아이템 획득
                }
                killedmonster.push_back(spawnedMonster.GetName());
                break;
            }

            spawnedMonster.takeDamage(myPlayer.GetAttack());
            cout << myPlayer.GetName() + "가 " + spawnedMonster.GetName() + "을 공격합니다! " + spawnedMonster.GetName() + " 체력: " + spawnedMonster.GetHP() << endl;

            if (myPlayer.GetHP) <= spawnedMonster.GetAttack())
            {
                myPlayer.SetHP(0);
                cout << spawnedMonster.GetName() + ".가 " + myPlayer.GetName() + "을 공격합니다! " + myPlayer.GetName() + " 체력: " + myPlayer.GetHP() << "→ 0" << endl;
                cout << myPlayer.GetName() + "가 사망했습니다. 게임 오버!" << endl;
                cout << "잡은 몬스터 : ";
                for (int i = 0; i < killedmonster.size(); i++)
                {
                    cout << killedmonster[i] + " ";
                }
                cout << endl;
                break;
                }
                myPlayer.SetHP(myPlayer.GetHP() - spawnedMonster.GetAttack());
                cout << spawnedMonster.GetName() + "가 " + myPlayer.GetName() + "을 공격합니다! " + myPlayer.GetName() + " 체력: " + myPlayer.GetHP() << endl;

                //TODO: 캐릭터 상태 확인하는 코드
                
        }


        spawnedMonster.reset();

        //포션으로 올라간 공격력을 낮춘다.
        if (ateattackpotion)
        {
            myPlayer.SetAttack(myPlayer.GetAttack() - 10);
            ateattackpotion = false;
        }


        if (myPlayer.GetHP() == 0)
        {
            break;
        }


        string yesornoString;
        //상점 방문 여부 확인
        while (true)
        {
            cout << "상점을 방문하시겠나요?(Y/N): ";

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
            std::vector<City> cities = getCities();
            City& currentCity = cities[0];
            goToStore(currentCity, myPlayer.GetInventory(), myPlayer.GetGold());
        }

    }
>>>>>>> feature/mainfeature

    return 0;
}