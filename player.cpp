#include <iostream>
#include "Monster.h"
#include "Player.h"

using namespace std;

Player :: Player(const string& playerName) 
	: playerName(playerName), level(1), curHealth(200), maxHealth(300), attack(30), experience(0) {}

const string& Player::get_playerName() const { return playerName; }
int Player::get_level() { return level; }
int Player::get_curHealth() { return curHealth; }
int Player::get_maxHealth() { return maxHealth; }
int Player::get_attack() { return attack; }
int Player::get_experience() { return experience; }

void Player::set_playerName(const string& playerName)
{
	this->playerName = playerName;
}
void Player::set_level(int level)
{
	this->level = level;
}
bool Player::set_curHealth(int curHealth)
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
void Player::set_attack(int attack)
{
	this->attack = attack;
}
void Player::set_experience(int experience)
{
	this->experience = experience;
}

void Player::PrintStatus()
{
	cout << "[  " << playerName << "님의 스탯 창  ]" << endl;
	cout << "Level : " << level << " | " << "현재 체력 : " << curHealth << " | "
		<< "공격력 : " << attack << " | " << "현재 경험치 : " << experience << endl;
}

