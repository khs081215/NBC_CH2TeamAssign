#include "MasterItems.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

// 내부 전용 함수: 문자열 → ShopType
static ShopType shopTypeFromString(std::string s)
{
    // 앞뒤 공백 제거 (JSON 실수 방어)
    s.erase(0, s.find_first_not_of(" \t\n\r"));
    s.erase(s.find_last_not_of(" \t\n\r") + 1);

    if (s == "General")    return ShopType::General;
    if (s == "Food")       return ShopType::Food;
    if (s == "Herbal")     return ShopType::Herbal;
    if (s == "Equipment")  return ShopType::Equipment;

    // 알 수 없는 값은 기본값으로 처리 (게임 안 죽게)
    return ShopType::General;
}

std::vector<std::unique_ptr<ItemBase>> getMasterItems()
{
    std::vector<std::unique_ptr<ItemBase>> items;

    std::ifstream file("items.json");
    if (!file.is_open())
        throw std::runtime_error("Failed to open items.json");

    json j;

    // 🔒 JSON 파싱 보호
    try {
        file >> j;
    }
    catch (const json::parse_error& e) {
        throw std::runtime_error(
            std::string("JSON parse error: ") + e.what()
        );
    }

    // 🔒 최상위는 반드시 배열이어야 함
    if (!j.is_array())
        throw std::runtime_error("items.json root must be an array");

    for (const auto& item : j)
    {
        try {
            // 필수 필드 검증
            if (!item.contains("type") ||
                !item.contains("name") ||
                !item.contains("description") ||
                !item.contains("price") ||
                !item.contains("value") ||
                !item.contains("shop"))
            {
                continue; // 하나라도 없으면 스킵
            }

            std::string type = item["type"].get<std::string>();
            std::string name = item["name"].get<std::string>();
            std::string desc = item["description"].get<std::string>();
            int price = item["price"].get<int>();
            int value = item["value"].get<int>();
            ShopType shop = shopTypeFromString(
                item["shop"].get<std::string>()
            );

            if (type == "Consumable")
            {
                items.push_back(
                    std::make_unique<Consumable>(name, desc, price, value, shop)
                );
            }
            else if (type == "Equipable")
            {
                items.push_back(
                    std::make_unique<Equipable>(name, desc, price, value, shop)
                );
            }
            // 알 수 없는 타입은 조용히 무시
        }
        catch (const std::exception&) {
            // 🔥 잘못된 아이템 하나 때문에 전체가 죽지 않게
            continue;
        }
    }

    return items;
}
