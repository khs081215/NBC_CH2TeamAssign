//KillMonsterQuest.cpp
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

    if (e.type == QuestEventType::KillMonster && e.target == targetMonster) {
        killCount += e.amount;

        if (killCount >= goal) {
            completed = true;
            justCompleted = true;  //  QuestManager용 플래그
        }
    }
}

std::string KillMonsterQuest::GetStatusText() const
{
    if (completed)
        return "[완료] " + title;

    return "[진행중] " + title + " (" + std::to_string(killCount) + "/" + std::to_string(goal) + ")";
}

int KillMonsterQuest::GetQuestId() const
{
    return questId;
}

// ⭐ Quest.h의 justCompleted 멤버 사용
bool KillMonsterQuest::JustCompleted()
{
    return justCompleted;
}

void KillMonsterQuest::ClearJustCompleted()
{
    justCompleted = false;
}
