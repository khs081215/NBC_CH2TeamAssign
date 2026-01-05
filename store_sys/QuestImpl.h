#pragma once
#include "Quest.h"
#include "QuestCondition.h"
#include "QuestEvent.h"
#include <vector>
#include <string>

class SimpleQuest : public Quest {
    std::string title;
    std::vector<QuestCondition> conditions;
    bool completed = false;

public:
    SimpleQuest(
        const std::string& t,
        std::vector<QuestCondition> conds
    );

    void OnEvent(const QuestEvent& e) override;
    std::string GetStatusText() const override;
    bool IsCompleted() const override { return completed; }
};
