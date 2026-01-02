#pragma once
#ifndef Player_H_
#define Player_H_

#include <iostream>
#include <string>
#include <vector>
#include "ItemType.h"

class Monster;
class Item;

class Player
{
protected:
	std::string playerName;
	int level;
	int curHealth;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	std::vector<Item*> inventory;
	// ================= 추가 멤버 변수 ================== //
	int bonusAttack = 0;
	// =============================================== //

public:
	Player(const std::string& playerName);
	~Player();

	void Attack(Monster* monster);
	void PrintStatus();
	//void UseItem(int index); // 기존 아이템 사용 함수
	bool UseItem(ItemType type); // (변경) 아이템 사용 함수
	bool ItemAutoUse();		// (추가) 아이템 자동 사용 함수
	void AddItem(Item* item);
	void LevelUP();

	const std::string& getplayerName() const;
	int getlevel() const;
	int getcurHealth() const;
	int getmaxHealth();
	int getattack() const;
	int getexperience();
	int getgold();

	void setplayerName(const std::string& playerName);
	void setlevel(int level);
	bool setcurHealth(int curHealth);
	void setattack(int attack);
	void setexperience(int experience);
	void setgold(int gold);

	// ======================== 아이템 사용 위한 추가 멤버 함수 =================== //
	void healthRestore(int restore);
	void IncreaseATK(int bonusAttack);
	void clearAttackBuff();
	// ==================================================================== //

};

#endif


