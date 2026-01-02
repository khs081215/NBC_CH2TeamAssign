#include "Monster.h"

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

bool Monster::SetHP(int inHP) {
    this->Hp = inHP;
    return true;
}

