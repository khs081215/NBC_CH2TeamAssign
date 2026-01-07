#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
using namespace std;

class Monster {
    // 자식 클래스에서 접근할 수 있도록 private 대신 protected 사용
protected: // 멤버 변수 : 이름, 레벨, HP, Atk
    string Name;
    int Level;
    int Hp;
    int Atk;

public:
    // 생성자에서 Level도 초기화 리스트에 포함해야 합니다.
    // 이름, 레벨, HP, Atk 호출
    Monster(int L, string inName);

    //메인 함수에 영향
    virtual void showInfo();
    virtual ~Monster() {}

    int getcurHealth();
    string GetName();
    int GetAttack();
    bool SetHP(int inHP);
    int GetLevel()const { return Level; }

    void setAtk(int NewAtk);
    virtual void display() = 0;
};


#endif