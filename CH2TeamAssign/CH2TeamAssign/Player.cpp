#include <iostream>
#include "Monster.h"
#include "Player.h"
#include "Item.h"

using namespace std;

Player::Player(const string& playerName)
	: playerName(playerName), level(1), curHealth(200), maxHealth(200), attack(30), experience(0), gold(0) {
}
Player ::~Player()
{
	for (Item* item : inventory)
	{
		delete item;
	}
}
const string& Player::getplayerName() const { return playerName; }
int Player::getlevel() const { return level; }
int Player::getcurHealth() const { return curHealth; }
int Player::getmaxHealth() { return maxHealth; }
int Player::getattack() const { return attack + bonusAttack; }		// 물약으로 얻는 추가 공격력까지 함께 반환 추가
int Player::getexperience() { return experience; }
int Player::getgold() { return gold; }

void Player::setplayerName(const string& playerName)
{
	this->playerName = playerName;
}
void Player::setlevel(int level)
{
	if (level <= 10)
	{
		this->level = level;
	}
	else
	{
		this->level = 10;
	}
}
bool Player::setcurHealth(int curHealth)
{
	if (curHealth < 0)
	{
		this->curHealth = 0;
	}
	else if (curHealth > maxHealth)
	{
		this->curHealth = maxHealth;
	}
	else
	{
		this->curHealth = curHealth;
	}
	return this->curHealth > 0;
}
void Player::setattack(int attack)
{
	this->attack = attack;
}
void Player::setexperience(int experience)
{
	this->experience += experience;

	if (this->experience >= 100 && level < 10)
	{
		this->experience -= 100;
		LevelUP();
	}
}
void Player::setgold(int gold)
{
	this->gold = gold;
}

void Player::PrintStatus()
{
	cout << "[  " << playerName << "님의 스탯 창  ]" << endl;
	cout << "Level : " << level << " | " << "현재 체력 : " << curHealth << " | "
		<< "공격력 : " << attack << " | " << "현재 경험치 : " << experience << " | "
		<< "현재 골드양 : " << gold << " | " << "현재 경험치 : " << experience << " /100" << endl;
}
void Player::LevelUP()
{
	if (level >= 10)
	{
		return;
	}
	cout << "레벨업 하였습니다\n";
	level++;
	maxHealth += level * 20;
	attack += level * 5;
	curHealth = maxHealth;
}
void Player::Attack(Monster* monster)
{
	bool isAlive = monster->SetHP(monster->getcurHealth() - (attack + bonusAttack));		// 물약 사용으로 인한 추가 공격력까지 반영된 데미지 계산
}

bool Player::UseItem(ItemType type)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if ((*it)->GetItemType() == type)
		{
			(*it)->Use(*this);
			delete* it;
			inventory.erase(it);
			return true;
		}
	}
	return false;
}

// 메인에서 공격전에 호출해주면 됨
// 1. 인벤토리가 비었다면 false 반환 > 공격 로직 호출
// 2. 아이템을 사용했다면 true 반환 > 턴 종료
bool Player::ItemAutoUse()
{
	// 인벤토리 비어 있으면 종료
	if (inventory.empty())
	{
		cout << "인벤토리가 비었습니다." << endl;
		return false;
	}

	const float hpRatio = static_cast<float>(curHealth) / maxHealth;
	// 체력 50% 이하 > 체력 물약
	if (hpRatio <= 0.5f)
	{
		if (Player::UseItem(ItemType::HealthPotion))
		{
			return true;
		}
	}
	// 체력 80% 이하 > 공격력 물약
	if (hpRatio <= 0.8f)
	{
		if (Player::UseItem(ItemType::AttackPotion))
		{
			return true;
		}
	}
	return false;
}

void Player::AddItem(Item* item)
{
	inventory.push_back(item);
}


// ============================ 아이템 사용 위한 추가 함수 ===================================== //
void Player::healthRestore(int restore)
{
	curHealth += restore;
	if (curHealth > maxHealth)
	{
		curHealth = maxHealth;
	}
}

void Player::IncreaseATK(int bonusATK)
{
	bonusAttack += bonusATK;
}

void Player::clearAttackBuff() {
	bonusAttack = 0;
}
// ======================================================================================= //