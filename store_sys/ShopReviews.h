#pragma once
#include <vector>
#include <string>
#include "ItemBase.h"   // ⭐ ShopType 여기 있음

class ShopReviews
{
public:
    static std::vector<std::string>
        getRandomReviews(ShopType type, int count);
};
