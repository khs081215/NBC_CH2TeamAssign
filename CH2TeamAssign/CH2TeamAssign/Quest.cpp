#include "Quest.h"

std::string Quest::GetStatusText() const {
    if (completed)
        return "[완료] " + title;
    else
        return "[진행중] " + title;
}
