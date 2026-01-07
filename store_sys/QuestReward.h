//QuestReward.h
#pragma once
#include <memory>
#include "Inventory.h"

class QuestReward {
public:
    virtual ~QuestReward() = default;
    virtual void Give(Inventory& inventory) = 0;
};
