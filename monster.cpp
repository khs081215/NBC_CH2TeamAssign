#include "Monster.h"
#include <cstdlib> // rand() 사용

Monster::Monster(int type, int playerLevel) {
    int baseHp = 0;
    int baseAttack = 0;

    // 1. 몬스터 종류 설정 (if-else 사용)
    if (type == 1) {
        name = "슬라임";
        baseHp = 60; baseAttack = 30;
        gold = 20; exp = 30;
    }
    else if (type == 2) {
        name = "고블린";
        baseHp = 70; baseAttack = 35;
        gold = 40; exp = 40;
    }
    else if (type == 3) {
        name = "오크";
        baseHp = 90; baseAttack = 50;
        gold = 50; exp = 60;
    }
    else {
        name = "(BOSS)트롤";
        baseHp = 120; baseAttack = 70;
        gold = 70; exp = 80;
    }

    // 2. 랜덤 스탯 계산 공식 적용
    // 체력 : 기본체력 + (레벨 * 20) ~ (레벨 * 30)
    int minHpBonus = playerLevel * 20;
    int maxHpBonus = playerLevel * 30;
    hp = baseHp + (minHpBonus + rand() % (maxHpBonus - minHpBonus + 1));

    // 공격력 : 기본공격력 + (레벨 * 5) ~ (레벨 * 10)
    int minAtkBonus = playerLevel * 5;
    int maxAtkBonus = playerLevel * 10;
    attack = baseAttack + (minAtkBonus + rand() % (maxAtkBonus - minAtkBonus + 1));
}

void Monster::printStatus() {
    std::cout << "======== [몬스터 등장] ========" << std::endl;
    std::cout << "이름: " << name << std::endl;
    std::cout << "체력: " << hp << " | 공격력: " << attack << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "처치 시 보상: " << gold << " Gold / " << exp << " EXP" << std::endl;
    std::cout << "============================\n" << std::endl;
}