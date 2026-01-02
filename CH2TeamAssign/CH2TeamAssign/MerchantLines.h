#pragma once
#include <map>
#include <vector>
#include <string>
#include "Store.h"

struct MerchantLines {
    static const std::map<MerchantPersonality, std::vector<std::string>> buyLines;
    static const std::map<MerchantPersonality, std::vector<std::string>> sellLines;
    static const std::map<MerchantPersonality, std::vector<std::string>> noGoldLines;
    static const std::map<MerchantPersonality, std::vector<std::string>> newStockLines;
};
