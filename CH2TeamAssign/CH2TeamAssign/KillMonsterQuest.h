//KillMonsterQuest.h
#pragma once
#include "Quest.h"
#include <string>

class KillMonsterQuest : public Quest {
    int questId;
    std::string title;
    std::string targetMonster;
    int killCount = 0;
    int goal;
    bool completed = false;
    bool popupShown = false;

public:
    KillMonsterQuest(int id, const std::string& t, const std::string& target, int g);

    void OnEvent(const QuestEvent& e) override;
    std::string GetStatusText() const override;
    
    int GetQuestId() const override;

    bool JustCompleted() override;
    void ClearJustCompleted() override;
};
