#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte   // Windows SDK의 byte typedef 제거

#include "Player.h"

void OpenInventory(Player& player);
