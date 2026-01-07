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
	int bonusAttack = 0;

public:
	Player(const std::string& playerName);
	~Player();

	void Attack(Monster* monster);  // 몬스터 공격(생사여부)
	void PrintStatus();             // 플레이어 상태창
	bool UseItem(ItemType type);    // 아이템 사용 함수
	bool ItemAutoUse();		        // 아이템 자동 사용 함수
	void AddItem(Item* item);       // 아이템 사용
	void LevelUP();                 // 레벨업

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


