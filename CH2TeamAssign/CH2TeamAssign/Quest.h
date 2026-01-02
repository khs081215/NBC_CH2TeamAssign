#pragma once
#include <string>
#include "QuestEvent.h"

class Quest {
protected:
    int questId = -1;
    bool completed = false;
    bool justCompleted = false;

public:
    virtual ~Quest() = default;

    virtual void OnEvent(const QuestEvent& e) = 0;
    virtual std::string GetStatusText() const = 0;
    virtual int GetQuestId() const = 0;
    virtual bool IsCompleted() const {
        return completed;
    }

    virtual bool JustCompleted() = 0;

    virtual void ClearJustCompleted() {
        justCompleted = false;
    }
};
