#include "SimpleQuest.h"

SimpleQuest::SimpleQuest(
    const std::string& t,
    std::vector<QuestCondition> conds
)
    : title(t), conditions(std::move(conds)) {
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
