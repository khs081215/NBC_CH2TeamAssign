#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <vector>
#include <string>
#include "ItemBase.h"


class Monster;

class Player {
protected:
    std::string playerName;
    int level;
    int curHealth;
    int maxHealth;
    int attack;
    int experience;
    int gold;

    std::vector<ItemBase*> inventory;
    ItemBase* equippedWeapon = nullptr;

public:
    Player(const std::string& name);
    ~Player();

    // Getter
    const std::string& getplayerName() const;
    int getlevel() const;
    int getcurHealth() const;
    int getmaxHealth();
    int getattack() const;
    int getexperience() const;
    int getgold() const;
    int& getGoldRef();

    // Setter
    void setplayerName(const std::string& name);
    void setlevel(int level);
    bool setcurHealth(int hp);
    void setattack(int atk);
    void setexperience(int exp);
    void setgold(int g);

    void PrintStatus();
    void LevelUP();
    void Attack(Monster* monster);

    void AddItem(ItemBase* item);
    void UseItem(int index);
    const std::vector<ItemBase*>& getInventory() const;

    void RestoreHP(int amount);
    void IncreaseATK(int amount);

    // Equipment
    void Equip(ItemBase* item);
    void UnequipWeapon();
    ItemBase* getEquippedWeapon() const;
};
