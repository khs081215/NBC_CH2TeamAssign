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
int Player::getattack() const { return attack; }
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
	level++;
	maxHealth += level * 20;
	attack += level * 5;
	curHealth = maxHealth;
}
void Player::Attack(Monster* monster)
{
	bool isAlive = monster->setHP(monster->getHP() - attack);
}

void Player::UseItem(int index)
{
	if (index < 0 || index >= (int)inventory.size())
	{
		cout << "아이템 인덱스가 잘못되었습니다." << endl;
		return;
	}
	inventory[index]->Use(*this);
}
void Player::AddItem(Item* item)
{
	inventory.push_back(item);
}