
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Player::Player(const string& name)
    : playerName(name), level(1), curHealth(200), maxHealth(200),
    attack(30), experience(0), gold(0), equippedWeapon(nullptr) {
}

Player::~Player() {
    for (ItemBase* item : inventory) delete item;
}

// ===== Getter =====
const string& Player::getplayerName() const { return playerName; }
int Player::getlevel() const { return level; }
int Player::getcurHealth() const { return curHealth; }
int Player::getmaxHealth() { return maxHealth; }
int Player::getattack() const { return attack; }
int Player::getexperience() const { return experience; }
int Player::getgold() const { return gold; }
int& Player::getGoldRef() { return gold; }

// ===== Setter =====
void Player::setplayerName(const string& name) { playerName = name; }
void Player::setlevel(int lvl) { level = min(lvl, 10); }
bool Player::setcurHealth(int hp) { curHealth = max(0, min(hp, maxHealth)); return curHealth > 0; }
void Player::setattack(int atk) { attack = atk; }
void Player::setexperience(int exp) { experience += exp; if (experience >= 100 && level < 10) { experience -= 100; LevelUP(); } }
void Player::setgold(int g) { gold = g; }

// ===== Status =====
void Player::PrintStatus() {
    cout << "[ " << playerName << " 상태 ]\n";
    cout << "LV " << level << " | HP " << curHealth << "/" << maxHealth
        << " | ATK " << attack << " | EXP " << experience << "/100 | GOLD " << gold << endl;
}

// ===== Battle =====
void Player::LevelUP() { level++; maxHealth += level * 20; attack += level * 5; curHealth = maxHealth; }
void Player::Attack(Monster* monster) { monster->setHP(monster->getHP() - attack); }

// ===== Inventory =====
void Player::AddItem(ItemBase* item) { inventory.push_back(item); }
void Player::UseItem(int idx) { if (idx >= 0 && idx < inventory.size()) inventory[idx]->Use(*this); }
const vector<ItemBase*>& Player::getInventory() const { return inventory; }

// ===== Stat Effects =====
void Player::RestoreHP(int amt) { curHealth = min(curHealth + amt, maxHealth); cout << playerName << " 체력 +" << amt << endl; }
void Player::IncreaseATK(int amt) { attack += amt; cout << playerName << " 공격력 " << (amt >= 0 ? "+" : "") << amt << endl; }

// ===== Equipment =====
void Player::Equip(ItemBase* item) {
    if (!item) return;
    if (equippedWeapon == item) { cout << "이미 장착 중\n"; return; }
    UnequipWeapon();
    equippedWeapon = item;
    if (Equipable* eq = dynamic_cast<Equipable*>(item)) IncreaseATK(eq->getAttackBoost());
}

void Player::UnequipWeapon() {
    if (!equippedWeapon) return;
    if (Equipable* eq = dynamic_cast<Equipable*>(equippedWeapon)) IncreaseATK(-eq->getAttackBoost());
    equippedWeapon = nullptr;
}

ItemBase* Player::getEquippedWeapon() const { return equippedWeapon; }
