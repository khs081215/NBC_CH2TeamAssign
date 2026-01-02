#include "QuestDatabase.h"

#include "QuestDatabase.h"

static std::vector<QuestData> gQuests = {
    {
        1,
        QuestType::KillMonster,
        "슬라임 5마리 처치",
        "슬라임",
        5,
        {} // 선행 없음
    },
    {
        2,
        QuestType::KillMonster,
        "고블린 10마리 처치",
        "고블린",
        10,
        { 1 } // ⭐ Quest 1 완료 필요
    },
    {
        3,
        QuestType::KillMonster,
        "늑대 3마리 처치",
        "늑대",
        3,
        { 2 } // ⭐ Quest 2 완료 필요
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
