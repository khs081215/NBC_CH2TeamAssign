#include "KillMonsterQuest.h"

KillMonsterQuest::KillMonsterQuest(
    int id,
    const std::string& t,
    const std::string& target,
    int g
)
{
    questId = id;
    title = t;
    targetMonster = target;
    goal = g;
}

void KillMonsterQuest::OnEvent(const QuestEvent& e)
{
    if (completed) return;

    if (e.type == QuestEventType::KillMonster &&
        e.target == targetMonster)
    {
        killCount += e.amount;

        if (killCount >= goal) {
            completed = true;
        }
    }
}

std::string KillMonsterQuest::GetStatusText() const
{
    if (completed)
        return "[완료] " + title;

    return "[진행중] " + title +
        " (" + std::to_string(killCount) +
        "/" + std::to_string(goal) + ")";
}

int KillMonsterQuest::GetQuestId() const
{
    return questId;
}

bool KillMonsterQuest::JustCompleted()
{
    if (completed && !popupShown) {
        popupShown = true;
        return true;
    }
    return false;
}
