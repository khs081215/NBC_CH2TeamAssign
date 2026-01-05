#include "SimpleQuest.h"

SimpleQuest::SimpleQuest(int id, const std::string& t, std::vector<QuestCondition> conds)
    : title(t), conditions(std::move(conds)) {
    questId = id;
    completed = false;
    justCompleted = false;
}

void SimpleQuest::OnEvent(const QuestEvent& e) {
    if (completed) return;

    for (auto& c : conditions) {
        c.OnEvent(e);
    }

    completed = true;
    for (const auto& c : conditions) {
        if (!c.IsSatisfied()) {
            completed = false;
            break;
        }
    }
}

std::string SimpleQuest::GetStatusText() const {
    if (completed)
        return title + " [요구사항 만족 완료]";
    else
        return title + " [진행 중]";
}

//  완료 순간 감지
bool SimpleQuest::JustCompleted() {
    if (completed && !justCompleted) {
        justCompleted = true;
        return true;
    }
    return false;
}

void SimpleQuest::ClearJustCompleted() {
    justCompleted = false;
}
