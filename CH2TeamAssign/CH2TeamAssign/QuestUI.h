#pragma once

#include <string>   // ⭐ 이 줄이 없어서 터진 것
class QuestManager;

void OpenQuestUI(QuestManager& questMgr);
void ShowQuestCompletePopup(const std::string& text);
