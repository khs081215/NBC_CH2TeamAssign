#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <string>
#include <memory>

#include "Inventory.h"
#include "ItemBase.h"
#include "ItemType.h"
#include "Monster.h"

class Player {
protected:
    // ===== 기본 스탯 =====
    std::string playerName;
    int level = 1;
    int curHealth = 200;
    int maxHealth = 200;

    int attack = 30;        // 기본 공격력
    int bonusAttack = 0;   // 추가 공격력 (포션 / 버프)

    int experience = 0;
    int gold = 0;

    // ===== 인벤토리 / 장비 =====
    Inventory inventory;
    ItemBase* equippedWeapon = nullptr;

public:
    // ===== 생성 / 소멸 =====
    Player(const std::string& name);
    ~Player();

    // ===== Getter (읽기 전용) =====
    const std::string& getplayerName() const;
    int getlevel() const;
    int getcurHealth() const;
    int getmaxHealth() const;
    int getattack() const;        // attack + bonusAttack
    int getexperience() const;
    int getgold() const;          // ⭐ 값 반환 (읽기용)

    // ===== Getter (수정용 참조) =====
    int& getGoldRef();             // ⭐ Store / UI에서 사용

    // ===== Inventory 접근 =====
    Inventory& GetInventory();
    const Inventory& GetInventory() const;

    // ===== Setter =====
    void setplayerName(const std::string& name);
    void setlevel(int lvl);
    bool setcurHealth(int hp);
    void setattack(int atk);
    void setexperience(int exp);
    void setgold(int g);

    // ===== Gameplay =====
    void PrintStatus();
    void LevelUP();
    void Attack(Monster* monster);

    // ===== Inventory / Item =====
    void UseItem(int index);
    bool UseItem(ItemType type);
    bool ItemAutoUse();
    void AddItem(std::unique_ptr<ItemBase> item);

    // ===== Status Effect =====
    void RestoreHP(int amount);
    void IncreaseATK(int amount);   // bonusAttack 증가
    void ClearAttackBuff();         // 전투 종료용

    // ===== Equipment =====
    void Equip(ItemBase* item);
    void UnequipWeapon();
    ItemBase* getEquippedWeapon() const;
};
