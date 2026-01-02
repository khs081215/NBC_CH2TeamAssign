#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte   // Windows SDK의 byte typedef 제거

#include <vector>
#include "City.h"

std::vector<City> getCities();
