#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include "Player.h"
#include "Inventory.h"
#include "ItemBase.h"
#include "Monster.h"

#include <iostream>
#include <algorithm>
#define COLOR_YELLOW "\033[33m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_RESET "\033[0m"
#define COLOR_REV_BLUE "\033[44m"
using namespace std;

Player::Player(const string& name)
    : playerName(name),
    level(1),
    curHealth(200),
    maxHealth(200),
    attack(30),
    bonusAttack(0),
    experience(0),
    gold(0),
    equippedWeapon(nullptr)
{
}

Player::~Player() {}


// ================= Getter =================
const string& Player::getplayerName() const { return playerName; }
int Player::getlevel() const { return level; }
int Player::getcurHealth() const { return curHealth; }
int Player::getmaxHealth() const { return maxHealth; }
int Player::getattack() const { return attack + bonusAttack; }
int Player::getexperience() const { return experience; }
int Player::getgold() const { return gold; }
int& Player::getGoldRef() { return gold; }


// ================= Setter =================
void Player::setplayerName(const string& name) { playerName = name; }

void Player::setlevel(int lvl) {
    level = min(lvl, 10);
}

bool Player::setcurHealth(int hp) {
    curHealth = max(0, min(hp, maxHealth));
    return curHealth > 0;
}

void Player::setattack(int atk) {
    attack = atk;
}

void Player::setexperience(int exp) {
    experience += exp;
    if (experience >= 100 && level < 10) {
        experience -= 100;
        LevelUP();
    }
}

void Player::setgold(int g) { gold = g; }


// ================= Status =================
void Player::PrintStatus() {
    cout << COLOR_YELLOW;
    cout << "[ " << playerName << " 상태 ]\n";
    cout << COLOR_RESET;
    cout << "LV " << level
        << " | HP " << curHealth << "/" << maxHealth
        << " | ATK " << attack << " (+" << bonusAttack << ")"
        << " | EXP " << experience << "/100"
        << " | GOLD " << gold << endl;
}


// ================= Level =================
void Player::LevelUP() {
    if (level >= 10) return;
    cout << COLOR_PURPLE;
    cout << "레벨업!\n";
    cout << COLOR_RESET;
    level++;
    //maxHealth += level * 20;
    //attack += level * 5;
    maxHealth += 20;
    attack += 5;
    curHealth = maxHealth;
}


// ================= Combat =================
void Player::Attack(Monster* monster) {
    int damage = getattack();
    int newHp = monster->getcurHealth() - damage;
    monster->SetHP(newHp);
}


// ================= Item =================
void Player::UseItem(int index) {
    inventory.UseItem(index, *this);
}

void Player::RestoreHP(int amt) {
    curHealth = min(curHealth + amt, maxHealth);
}

void Player::IncreaseATK(int amt) {
    bonusAttack += amt;
}

void Player::ClearAttackBuff() {
    bonusAttack = 0;
}


// ================= Auto Item =================
bool Player::ItemAutoUse()
{
    if (inventory.empty())
    {
        return false;
    }

    float hpRatio = static_cast<float>(curHealth) / maxHealth;

    // HP 50% 이하 = 체력 포션
    if (hpRatio <= 0.5f)
    {
        for (int i = 0; i < inventory.GetItemCount(); ++i)
        {
            ItemBase* item = inventory.GetItem(i);
            if (!item) continue;

            if (item->GetItemType() == ItemType::HealthPotion)
            {
                cout << COLOR_REV_BLUE;
                inventory.UseItem(i, *this);
                cout << COLOR_RESET;
                return true;
            }
        }
    }

    // HP 80% 이하 = 공격 포션
    if (hpRatio <= 0.8f)
    {
        for (int i = 0; i < inventory.GetItemCount(); ++i)
        {
            ItemBase* item = inventory.GetItem(i);
            if (!item) continue;

            if (item->GetItemType() == ItemType::AttackPotion)
            {
                cout << COLOR_REV_BLUE;
                inventory.UseItem(i, *this);
                cout << COLOR_RESET;
                return true;
            }
        }
    }

    return false;
}


// ================= Equipment =================
void Player::Equip(ItemBase* item) {
    if (!item) return;

    auto* eq = dynamic_cast<Equipable*>(item);
    if (!eq) return;

    if (equippedWeapon)
        UnequipWeapon();

    equippedWeapon = item;
    IncreaseATK(eq->getAttackBoost());

    cout << eq->getName() << " 장착!\n";
}

void Player::UnequipWeapon() {
    if (!equippedWeapon) return;

    auto* eq = dynamic_cast<Equipable*>(equippedWeapon);
    if (eq)
        IncreaseATK(-eq->getAttackBoost());

    equippedWeapon = nullptr;
}

ItemBase* Player::getEquippedWeapon() const {
    return equippedWeapon;
}


// ================= Inventory =================
void Player::AddItem(std::unique_ptr<ItemBase> item)
{
    inventory.AddItem(std::move(item));
}

// ================= Inventory Getter =================
Inventory& Player::GetInventory()
{
    return inventory;
}

const Inventory& Player::GetInventory() const
{
    return inventory;
}
