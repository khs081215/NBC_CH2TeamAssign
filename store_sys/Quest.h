//Quest.h
#pragma once
#include <string>
#include <memory>
#include "QuestEvent.h"
#include "QuestReward.h"
#include "Inventory.h"

class Quest {
protected:
    int questId = -1;
    bool completed = false;
    bool justCompleted = false;
    bool rewardGiven = false;

    std::unique_ptr<QuestReward> reward;   // ⭐ 추가

public:
    virtual ~Quest() = default;

    // ===== 보상 관련 =====
    void SetReward(std::unique_ptr<QuestReward> r) {
        reward = std::move(r);
    }

    void GiveReward(Inventory& inventory) {
        if (reward)
            reward->Give(inventory);
    }

    virtual void MarkRewardGiven() { rewardGiven = true; }
    virtual bool IsRewardGiven() const { return rewardGiven; }

    // ===== 퀘스트 기본 =====
    virtual void OnEvent(const QuestEvent& e) = 0;
    virtual std::string GetStatusText() const = 0;
    virtual int GetQuestId() const = 0;

    virtual bool IsCompleted() const {
        return completed;
    }

    // ===== 완료 순간 감지 =====
    virtual bool JustCompleted() = 0;

    virtual void ClearJustCompleted() {
        justCompleted = false;
    }
};
