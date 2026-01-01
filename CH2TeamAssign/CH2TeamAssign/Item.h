#pragma once
#ifndef Item_H_
#define Item_H_
#include <string>
#include "ItemType.h"

class Player;

class Item {
protected:
    std::string name;
    ItemType type;
    int price;
public:
    virtual ~Item() = default;

    std::string GetName() const { return name; };    //  name getter 함수
    int GetPrice() const { return price; };                  // price getter 함수
    ItemType GetItemType() const { return type; };           // item type getter 함수
    virtual void Use(Player& player) = 0;       // player 에게 아이템 사용 호출 함수
};
#endif
