// QuestFactory.cpp
#include <memory>          
#include <string>

#include "QuestFactory.h" 
#include "QuestData.h"     // QuestData, QuestType
#include "KillMonsterQuest.h"



std::unique_ptr<Quest> QuestFactory::CreateFromData(
    const QuestData& data
)
{
    switch (data.type) {

    case QuestType::KillMonster:
        return std::make_unique<KillMonsterQuest>(
            data.id,        
            data.title,
            data.target,
            data.count
        );

    default:
        return nullptr;
    }
}
