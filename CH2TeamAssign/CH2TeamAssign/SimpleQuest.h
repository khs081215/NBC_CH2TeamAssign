#pragma once
#include "Quest.h"
#include "QuestCondition.h"
#include "QuestEvent.h"
#include <string>
#include <vector>

class SimpleQuest : public Quest {
    std::string title;
    std::vector<QuestCondition> conditions;
    bool completed = false;

public:
    // Constructor
    SimpleQuest(const std::string& t, std::vector<QuestCondition> conds);

    // Handle an event
    void OnEvent(const QuestEvent& e) override;

    // Get quest status as string
    std::string GetStatusText() const override;

    // Check if quest is completed
    bool IsCompleted() const override { return completed; }
};
