#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
using namespace std;

class Monster {
protected: // 멤버 변수 : 이름, 레벨, HP, Atk
    string Name;
    int Level;
    int Hp;
    int Atk;

public:
    // 이름, 레벨, HP, Atk 호출
    Monster(string N, int L, int H, int A) : Name(N), Level(L), Hp(H), Atk(A) {}

    //메인 함수에 영향
    virtual void showInfo();
    virtual ~Monster() {}
};

#endif