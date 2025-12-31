#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

class Monster {
public:
    std::string name;
    int hp;
    int attack;
    int gold;
    int exp;

    // 생성자: 타입에 따라 초기화
    Monster(int type, int playerLevel);

    // 정보 출력 함수
    void printStatus();
};

#endif