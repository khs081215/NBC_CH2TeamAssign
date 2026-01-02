#pragma once
#include <vector>
#include "QuestData.h"

class QuestDatabase {
public:
    static const std::vector<QuestData>& GetAllQuests();
    static const QuestData* GetQuestById(int id);
};
