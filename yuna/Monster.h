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
    // 생성자에서 Level도 초기화 리스트에 포함해야 합니다.
    // 이름, 레벨, HP, Atk 호출
    Monster(int L, string N);

    //메인 함수에 영향
    virtual void showInfo();
    virtual ~Monster();

    // get 함수 (Getter): 멤버 변수 값 반환
    string getName() const { return Name; }
    int getLevel() const { return Level; }
    int getHp() const { return Hp; }
    int getAtk() const { return Atk; }

    // set 함수 (Setter): 멤버 변수 값 설정
    void setHp(const int NewHp);
    void setAtk(int NewAtk);
};

#endif