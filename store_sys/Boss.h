#pragma once
#ifndef BOSS_H
#define BOSS_H

#include "Monster.h"

class Boss : public Monster {
public:

    Boss(int playerLevel);


    void showInfo() override;
    void display();
};

#endif