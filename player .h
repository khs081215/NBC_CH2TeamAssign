#pragma once
#include <iostream>
#include <string>

using namespace std;

class Monster;

class Player
{
protected :
	string playerName;
	int level;
	int curHealth;
	int maxHealth;
	int attack;
	int experience;

public :
	Player(const string& playerName);

	void Attack(Monster* monster);
	void PrintStatus();

	const string& get_playerName() const;
	int get_level();
	int get_curHealth();
	int get_maxHealth();
	int get_attack();
	int get_experience();

	void set_playerName(const string& playerName);
	void set_level(int level);
	bool set_curHealth(int curHealth);
	void set_attack(int attack);
	void set_experience(int experience);
};