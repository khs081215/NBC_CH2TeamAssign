#pragma once
#include "Quest.h"
#include "QuestCondition.h"
#include "QuestEvent.h"
#include <string>
#include <vector>

class SimpleQuest : public Quest {
    std::string title;
    std::vector<QuestCondition> conditions;

public:
    // Constructor
    SimpleQuest(int id, const std::string& t, std::vector<QuestCondition> conds);

    // Handle an event
    void OnEvent(const QuestEvent& e) override;

    // Get quest status as string
    std::string GetStatusText() const override;

    // Quest ID
    int GetQuestId() const override { return questId; }

    // Completion checks
    bool IsCompleted() const override { return completed; }
    bool JustCompleted() override;
    void ClearJustCompleted() override;

private:
    bool completed = false;
};
