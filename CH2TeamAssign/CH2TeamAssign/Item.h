#pragma once
#ifndef Item_H_
#define Item_H_
#include <string>

class Player;

class Item {
public:
    virtual ~Item() = default;

    virtual std::string getName() const = 0;
    virtual void Use(Player& player) = 0;
};

#endif


