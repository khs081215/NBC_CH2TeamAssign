//QuestDatabase.cpp
#include "QuestDatabase.h"

#include "QuestDatabase.h"

static std::vector<QuestData> gQuests = {
    {
        1,
        QuestType::KillMonster,
        "Slime 5마리 처치",
        "Slime",
        5,
        {} // 선행 없음
    },
    {
        2,
        QuestType::KillMonster,
        "Goblin 10마리 처치",
        "Goblin",
        10,
        { 1 } //  Quest 1 완료 필요
    },
    {
        3,
        QuestType::KillMonster,
        " Orc 3마리 처치",
        "Orc",
        3,
        { 2 } //  Quest 2 완료 필요
    }
};


const QuestData* QuestDatabase::GetQuestById(int id) {
    for (auto& q : gQuests)
        if (q.id == id) return &q;
    return nullptr;
}

const std::vector<QuestData>& QuestDatabase::GetAllQuests() {
    return gQuests;
}
