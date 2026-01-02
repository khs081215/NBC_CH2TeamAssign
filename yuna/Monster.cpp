#include "Monster.h"
#include <ctime>
#include <cstdlib>




    Monster::Monster(int L, string N)
    {
        Name = N;
        Level = L;
    
         Hp = rand() % (L * 10 + 1) + (L * 20);
         Atk = rand() % (L * 5 + 1) + (L * 5);

    }
   
    void Monster::showInfo() {
        cout << "[" << Name << "] Level: " << Level << " | Hp: " << Hp << " | Atk: " << Atk << endl;
    }
    //출력 : 이름, 레벨, HP, Atk

    // set 함수 (Setter): 멤버 변수 값 설정
    void Monster::setHp(const int NewHp)
    {
        Hp = (NewHp > 0) ? NewHp : 0;   // HP가 음수가 되지 않도록 유효성 검사
    }
    void Monster::setAtk(int NewAtk)
    {
        Atk = NewAtk;
    }
