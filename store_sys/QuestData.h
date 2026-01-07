//QuestData.h
#pragma once
#include <string>
#include <vector>

enum class QuestType {
    KillMonster,
    // FetchItem,
    // TalkToNPC,
};

struct QuestData {
    int id;
    QuestType type;

    std::string title;

    // Kill quest
    std::string target;
    int count;
    std::vector<int> prerequisites;
};
