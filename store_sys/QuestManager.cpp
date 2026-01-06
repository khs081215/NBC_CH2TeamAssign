//QuestManager.cpp
#include "QuestManager.h"

bool QuestManager::CanAcceptQuest(const QuestData& data) const {
    if (IsQuestCompleted(data.id)) return false;
    if (IsQuestAccepted(data.id)) return false;
    for (int preId : data.prerequisites)
        if (!IsQuestCompleted(preId)) return false;
    return true;
}

void QuestManager::TakeQuest(std::unique_ptr<Quest> q, int questId) {
    acceptedQuestIds.push_back(questId);
    activeQuests.push_back(std::move(q));
}

bool QuestManager::IsQuestAccepted(int questId) const {
    return std::find(acceptedQuestIds.begin(), acceptedQuestIds.end(), questId) != acceptedQuestIds.end();
}

bool QuestManager::IsQuestCompleted(int questId) const {
    return std::find(completedQuestIds.begin(), completedQuestIds.end(), questId) != completedQuestIds.end();
}

const std::vector<std::unique_ptr<Quest>>& QuestManager::GetActiveQuests() const {
    return activeQuests;
}

/* =========================
   이벤트 전달 (핵심 수정)
========================= */
void QuestManager::Notify(const QuestEvent& e) {
    for (auto& q : activeQuests) {
        q->OnEvent(e);

        if (q->JustCompleted() && !q->IsRewardGiven()) {

            // 1️⃣ 완료 팝업
            if (popupHandler)
                popupHandler(q->GetStatusText());

            // 2️⃣ 보상 지급
            if (inventory)
                q->GiveReward(*inventory);

            // 3️⃣ 완료 처리
            q->MarkRewardGiven();
            completedQuestIds.push_back(q->GetQuestId());
        }
    }
}
