#include "Monster.h"
#include <ctime>

void Monster::showInfo() {
    cout << "[" << Name << "] Level: " << Level << " | Hp: " << Hp << " | Atk: " << Atk << endl;
}
//출력 : 이름, 레벨, HP, Atk

int Monster::getcurHealth() {
    return this->Hp;
}

string Monster::GetName() {
    return this->Name;
}

int Monster::GetAttack() {
    return this->Atk;
}

bool Monster::SetHP(int NewHp) {
    Hp = (NewHp > 0) ? NewHp : 0;
    return true;
}

void Monster::setAtk(int NewAtk)
{
    Atk = NewAtk;
}

Monster::Monster(int L, string inName = "default")
{
    srand((unsigned int)time(NULL));
    Name = inName;
    Level = L;
    Hp = rand() % (L * 10 + 1) + (L * 20);         //Hp 랜덤하게
    Atk = rand() % (L * 5 + 1) + (L * 5);          //Atk 랜덤하게
}

