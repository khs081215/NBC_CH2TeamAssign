// QuestDatabase.cpp
#include "QuestDatabase.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

static std::vector<QuestData> gQuests;

static QuestType ParseQuestType(const std::string& type)
{
    if (type == "KillMonster")
        return QuestType::KillMonster;

    return QuestType::KillMonster;
}

static void LoadQuestsFromJson()
{
    if (!gQuests.empty())
        return;

    std::ifstream file("quests.json");
    if (!file.is_open())
    {
        std::cerr << "Failed to open quests.json\n";
        return;
    }

    json j;
    file >> j;

    for (const auto& q : j["quests"])
    {
        QuestData data;
        data.id = q["id"];
        data.type = ParseQuestType(q["type"]);
        data.title = q["title"];
        data.target = q["target"];          
        data.count = q["count"];            
        data.prerequisites = q["prerequisites"].get<std::vector<int>>();

        gQuests.push_back(data);
    }
}

const QuestData* QuestDatabase::GetQuestById(int id)
{
    LoadQuestsFromJson();

    for (auto& q : gQuests)
        if (q.id == id)
            return &q;

    return nullptr;
}

const std::vector<QuestData>& QuestDatabase::GetAllQuests()
{
    LoadQuestsFromJson();
    return gQuests;
}
