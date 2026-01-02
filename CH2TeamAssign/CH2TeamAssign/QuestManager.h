#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "Quest.h"
#include "QuestEvent.h"
#include "QuestData.h"     // ⭐ 추가

class QuestManager {
    std::vector<std::unique_ptr<Quest>> activeQuests;
    std::vector<int> acceptedQuestIds;    // 이미 수락한 퀘스트
    std::vector<int> completedQuestIds;   // ⭐ 완료된 퀘스트
    

public:
    void TakeQuest(std::unique_ptr<Quest> q, int questId);

    bool IsQuestAccepted(int questId) const;
    bool IsQuestCompleted(int questId) const;

    // ⭐ 새로 추가
    bool CanAcceptQuest(const QuestData& data) const;

    void Notify(const QuestEvent& e);
    std::vector<Quest*> GetJustCompletedQuests();
    const std::vector<std::unique_ptr<Quest>>& GetActiveQuests() const;
};
