#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "Player.h"
#include "Inventory.h"
#include "ItemBase.h"
#include "Monster.h"

#include <iostream>
using namespace std;

Player::Player(const string& name)
    : playerName(name), level(1), curHealth(200), maxHealth(200),
    attack(30), experience(0), gold(0), equippedWeapon(nullptr) {
}

Player::~Player() {}

const string& Player::getplayerName() const { return playerName; }
int Player::getlevel() const { return level; }
int Player::getcurHealth() const { return curHealth; }
int Player::getmaxHealth() const { return maxHealth; }
int Player::getattack() const { return attack; }
int Player::getexperience() const { return experience; }
int Player::getgold() const { return gold; }
int& Player::getGoldRef() { return gold; }

void Player::setplayerName(const string& name) { playerName = name; }
void Player::setlevel(int lvl) { level = min(lvl, 10); }
bool Player::setcurHealth(int hp) {
    curHealth = max(0, min(hp, maxHealth));
    return curHealth > 0;
}
void Player::setattack(int atk) { attack = atk; }
void Player::setexperience(int exp) {
    experience += exp;
    if (experience >= 100 && level < 10) {
        experience -= 100;
        LevelUP();
    }
}
void Player::setgold(int g) { gold = g; }

void Player::PrintStatus() {
    cout << "[ " << playerName << " 상태 ]\n";
    cout << "LV " << level
        << " | HP " << curHealth << "/" << maxHealth
        << " | ATK " << attack
        << " | EXP " << experience << "/100"
        << " | GOLD " << gold << endl;
}

void Player::LevelUP() {
    level++;
    maxHealth += level * 20;
    attack += level * 5;
    curHealth = maxHealth;
}

void Player::Attack(Monster* monster) {
    monster->setHP(monster->getHP() - attack);
}

void Player::UseItem(int index) {
    inventory.UseItem(index, *this);
}

void Player::RestoreHP(int amt) {
    curHealth = min(curHealth + amt, maxHealth);
    cout << playerName << " 체력 +" << amt << endl;
}

void Player::IncreaseATK(int amt) {
    attack += amt;
    cout << playerName << " 공격력 " << (amt >= 0 ? "+" : "") << amt << endl;
}

void Player::Equip(ItemBase* item) {
    if (!item) return;

    auto* eq = dynamic_cast<Equipable*>(item);
    if (!eq) return;

    if (equippedWeapon) UnequipWeapon();

    equippedWeapon = item;
    IncreaseATK(eq->getAttackBoost());

    cout << eq->getName() << " 장착!\n";
}

void Player::UnequipWeapon() {
    if (!equippedWeapon) return;

    auto* eq = dynamic_cast<Equipable*>(equippedWeapon);
    if (eq) IncreaseATK(-eq->getAttackBoost());

    equippedWeapon = nullptr;
}

ItemBase* Player::getEquippedWeapon() const { return equippedWeapon; }
