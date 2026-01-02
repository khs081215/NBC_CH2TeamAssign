#include "QuestManager.h"
#include <algorithm>

/* =========================
   퀘스트 수락 가능 여부
========================= */
bool QuestManager::CanAcceptQuest(const QuestData& data) const {
    // ⭐ 이미 완료한 퀘스트면 수락 불가
    if (IsQuestCompleted(data.id))
        return false;

    // 이미 수락 중이면 불가
    if (IsQuestAccepted(data.id))
        return false;

    // 선행 퀘스트 체크
    for (int preId : data.prerequisites) {
        if (!IsQuestCompleted(preId))
            return false;
    }

    return true;
}


/* =========================
   퀘스트 수락
========================= */
void QuestManager::TakeQuest(std::unique_ptr<Quest> q, int questId)
{
    acceptedQuestIds.push_back(questId);
    activeQuests.push_back(std::move(q));
}

/* =========================
   수락 여부 확인
========================= */
bool QuestManager::IsQuestAccepted(int questId) const
{
    return std::find(
        acceptedQuestIds.begin(),
        acceptedQuestIds.end(),
        questId
    ) != acceptedQuestIds.end();
}

/* =========================
   이벤트 전달
========================= */
void QuestManager::Notify(const QuestEvent& e)
{
    for (int i = 0; i < activeQuests.size(); ++i) {
        auto& q = activeQuests[i];
        q->OnEvent(e);

        if (q->IsCompleted()) {
            int questId = q->GetQuestId();

            // 이미 완료 목록에 없으면 기록
            if (!IsQuestCompleted(questId)) {
                completedQuestIds.push_back(questId);
            }
        }
    }
}



/* =========================
   완료 여부 확인
========================= */
bool QuestManager::IsQuestCompleted(int questId) const
{
    return std::find(
        completedQuestIds.begin(),
        completedQuestIds.end(),
        questId
    ) != completedQuestIds.end();
}

/* =========================
   진행 중 퀘스트 목록
========================= */
const std::vector<std::unique_ptr<Quest>>&
QuestManager::GetActiveQuests() const
{
    return activeQuests;
}

/* =========================
   방금 완료된 퀘스트 (소비형)
========================= */
std::vector<Quest*> QuestManager::GetJustCompletedQuests()
{
    std::vector<Quest*> result;

    for (auto& q : activeQuests) {
        if (q->JustCompleted()) {
            result.push_back(q.get());
            q->ClearJustCompleted();   // ⭐ 핵심
        }
    }

    return result;
}
