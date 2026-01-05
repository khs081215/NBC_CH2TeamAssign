// QuestFactory.cpp
#include <memory>
#include <string>

#include "QuestFactory.h"
#include "QuestData.h"
#include "KillMonsterQuest.h"

//  Low-level: 직접 퀘스트 생성 (테스트/특수 상황용)
std::unique_ptr<Quest> QuestFactory::CreateKillQuest(
    const std::string& title,
    const std::string& target,
    int count
) {
    // id는 임시로 0, 실제 게임에서는 별도 관리 필요
    int id = 0;
    return std::make_unique<KillMonsterQuest>(id, title, target, count);
}

//  High-level: 데이터 기반 생성 (실제 게임용)
std::unique_ptr<Quest> QuestFactory::CreateFromData(const QuestData& data) {
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

