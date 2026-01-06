#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte

#include <iostream>
#include "ItemBase.h"
#include "Player.h"

class HealthPotion : public ItemBase {
private:
    std::string name = "Health Potion"; // 기존 멤버
    int HealthRestore = 50;
    int price = 10;

public:
    // 기존 내 HealthPotion 기능 그대로
    std::string virtualGetName() const override { return name; }
    int virtualGetPrice() const override { return price; }
    void Use(Player& player) override;

    // 팀 리드 기능 호환용
    ItemType GetItemType() const override { return ItemType::HealthPotion; }
};

// cpp에서 구현
void HealthPotion::Use(Player& player) {
    player.RestoreHP(HealthRestore);
    std::cout << "체력 포션 사용! +" << HealthRestore << " HP\n";
}
