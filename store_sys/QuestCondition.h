#pragma once
#include "QuestEvent.h"

struct QuestCondition {
    QuestEventType type;
    std::string target;
    int requiredCount;
    int currentCount = 0;

    bool IsSatisfied() const {
        return currentCount >= requiredCount;
    }

    void OnEvent(const QuestEvent& e) {
        if (e.type == type && e.target == target) {
            currentCount += e.amount;
        }
    }
};
