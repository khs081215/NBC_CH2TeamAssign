// 김태우_테스트용 플레이어 클래스
#pragma once
#ifndef Player_H_
#define Player_H_

class Player {
private:
    int maxHealth = 30;
    int currentHealth = 30;
    int attack = 10;
    int bonusAttack = 0;

public:
    void RestoreHP(int restore);
    void IncreaseATK(int increase);
    void EndBuff();
    void TakeDamage(int damage);
    void ViewATK();
};

#endif


