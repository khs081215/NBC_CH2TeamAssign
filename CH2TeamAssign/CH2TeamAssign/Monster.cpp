#include "Monster.h"
﻿#include "Monster.h"
#include <ctime>

void Monster::showInfo() {
    //출력 : 이름, 레벨, HP, Atk
    cout << "[" << Name << "] Level: " << Level << " | Hp: " << Hp << " | Atk: " << Atk << endl;
}


public : 

    Monster(int L, string inName = "default")
    {
        srand(unsigned int)time(NULL));
        Name = inName;
        Level = L;
        Hp = rand()%(L * 10 + 1) + (L * 20);         //Hp 랜덤하게
        Atk = rand()%(L * 5 + 1) + (L * 5);          //Atk 랜덤하게
    }

// set 함수 (Setter): 멤버 변수 값 설정
void Monster::setHp(const string& NewHp) 
{
    Hp = (NewHp > 0) ? NewHp : 0;   // HP가 음수가 되지 않도록 유효성 검사
}
void Monster::setAtk(int NewAtk) 
{
    Atk = NewAtk; 
}



