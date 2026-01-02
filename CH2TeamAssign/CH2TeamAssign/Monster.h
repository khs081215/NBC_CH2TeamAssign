#pragma once
﻿#pragma once

#ifndef MONSTER_H
#define MONSTER_H

@@ - 8, 16 + 8, 17 @@
using namespace std;

class Monster {
protected: // 자식 클래스에서 접근할 수 있도록 private 대신 protected 사용
protected: // 멤버 변수 : 이름, 레벨, HP, Atk
    string Name;
    int Level;
    int Hp;
    int Atk;

public:
    // 생성자에서 Level도 초기화 리스트에 포함해야 합니다.
    // 이름, 레벨, HP, Atk 호출
    Monster(int L, string inName = " ")
 

    //메인 함수에 영향
    virtual void showInfo();
    virtual ~Monster();

    // get 함수 (Getter): 멤버 변수 값 반환
    string getName() const { return Name; }
    int getLevel() const { return Level; }
    int getHp() const { return Hp; }
    int getAtk() const { return Atk; }

    // set 함수 (Setter): 멤버 변수 값 설정
    void setHp(const string& NewHp);
    void setAtk(int NewAtk);


};

