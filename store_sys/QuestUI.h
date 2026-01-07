//QuestUI.h
#pragma once

#include <string>
class QuestManager;

void OpenQuestUI(QuestManager& questMgr);
void ShowQuestCompletePopup(const std::string& text);
