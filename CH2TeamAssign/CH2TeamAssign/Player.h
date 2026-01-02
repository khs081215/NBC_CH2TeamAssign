#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <string>
#include "Inventory.h"

class ItemBase;
class Monster;

class Player {
private:
    Inventory inventory;
    ItemBase* equippedWeapon = nullptr;

protected:
    std::string playerName;
    int level = 1;
    int curHealth = 100;
    int maxHealth = 100;
    int attack = 10;
    int experience = 0;
    int gold = 0;

public:
    Player(const std::string& name);
    ~Player();

    // ===== Getter =====
    const std::string& getplayerName() const;
    int getlevel() const;
    int getcurHealth() const;
    int getmaxHealth() const;
    int getattack() const;
    int getexperience() const;
    int getgold() const;
    int& getGoldRef();

    // ===== Setter =====
    void setplayerName(const std::string& name);
    void setlevel(int level);
    bool setcurHealth(int hp);
    void setattack(int atk);
    void setexperience(int exp);
    void setgold(int g);

    // ===== Gameplay =====
    void PrintStatus();
    void LevelUP();
    void Attack(Monster* monster);

    // ===== Inventory bridge =====
    Inventory& GetInventory() { return inventory; }
    const Inventory& GetInventory() const { return inventory; }
    void UseItem(int index);   // inventory.UseItem 위임

    // ===== Status effect =====
    void RestoreHP(int amount);
    void IncreaseATK(int amount);

    // ===== Equipment =====
    void Equip(ItemBase* item);
    void UnequipWeapon();
    ItemBase* getEquippedWeapon() const;
};
