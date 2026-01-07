//QuestEvent.h
#pragma once
#include <string>

enum class QuestEventType {
    BuyItem,
    SellItem,
    UseItem,
    KillMonster,
    EnterCity,
};

struct QuestEvent {
    QuestEventType type;
    std::string target; // 아이템 이름, 몬스터 이름, 도시 이름
    int amount;
};
