#pragma once
#ifndef Item_H_
#define Item_H_
#include <string>

class Player;

class Item {
public:
    virtual ~Item() = default;

    virtual std::string getName() const = 0;    //  name getter 함수
    virtual int getPrice() const = 0;                // price getter 함수
    virtual void Use(Player& player) = 0;       // player 에게 아이템 사용 호출 함수
};
#endif
