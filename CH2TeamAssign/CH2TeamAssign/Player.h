#pragma once
#ifndef Player_H_
#define Player_H_

#include <iostream>
#include <string>
#include <vector>

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

public:
	Player(const std::string& playerName);
	~Player();

	void Attack(Monster* monster);
	void PrintStatus();
	void UseItem(int index);
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
};

#endif


