#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
class Monster {
private:
    int hp;

public:
    Monster(int hp = 100) : hp(hp) {}

    int getHP() const {
        return hp;
    }

    // Player::Attack에서 bool을 기대하므로 bool 반환
    bool setHP(int newHP) {
        hp = newHP;
        return hp > 0;
    }
};
