// QuestFactory.h
#pragma once

#include <memory>
#include <string>

#include "Quest.h"
#include "QuestData.h"

class QuestFactory {
public:
    // 🔹 Low-level: 직접 퀘스트 생성 (테스트/특수 상황용)
    static std::unique_ptr<Quest> CreateKillQuest(
        const std::string& title,
        const std::string& target,
        int count
    );

    // 🔹 High-level: 데이터 기반 생성 (실제 게임용)
    static std::unique_ptr<Quest> CreateFromData(
        const QuestData& data
    );
};
