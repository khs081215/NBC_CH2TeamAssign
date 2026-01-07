//QuestManager.h
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include "Quest.h"
#include "QuestData.h"
#include "QuestEvent.h"
#include "Inventory.h" 
class QuestManager {
    std::vector<std::unique_ptr<Quest>> activeQuests;
    std::vector<int> acceptedQuestIds;
    std::vector<int> completedQuestIds;
    Inventory* inventory = nullptr;

public:
    void SetInventory(Inventory* inv) { inventory = inv; }
    void TakeQuest(std::unique_ptr<Quest> q, int questId);
    bool IsQuestAccepted(int questId) const;
    bool IsQuestCompleted(int questId) const;
    bool CanAcceptQuest(const QuestData& data) const;

    const std::vector<std::unique_ptr<Quest>>& GetActiveQuests() const;

    void Notify(const QuestEvent& e);

    // ⭐ 콜백
    std::function<void(const std::string&)> popupHandler;
    std::function<void(Quest*)> rewardHandler;

    void SetPopupHandler(std::function<void(const std::string&)> handler) { popupHandler = handler; }
    void SetRewardHandler(std::function<void(Quest*)> handler) { rewardHandler = handler; }
};
