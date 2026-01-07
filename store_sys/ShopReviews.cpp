#include "ShopReviews.h"
#include <fstream>
#include <random>
#include "json.hpp"

using json = nlohmann::json;

namespace
{
    std::mt19937& rng()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    bool chance(int percent)
    {
        std::uniform_int_distribution<> dist(1, 100);
        return dist(rng()) <= percent;
    }

    std::string jsonPathFromShopType(ShopType type)
    {
        switch (type)
        {
        case ShopType::Equipment: return "Equipment_reviews.json";
        case ShopType::Food:      return "Food_reviews.json";
        case ShopType::Herbal:    return "Herbal_reviews.json";
        case ShopType::General:   return "General_reviews.json";
        default:                  return "General_reviews.json";
        }
    }

    std::vector<std::string> loadReviews(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            return { "⭐️⭐️⭐️ 후기가 없어서 불안하다" };

        json j;
        try { file >> j; }
        catch (...) { return { "⭐️⭐️⭐️ 후기 파일이 깨졌다" }; }

        if (!j.contains("reviews") || !j["reviews"].is_array())
            return { "⭐️⭐️⭐️ 후기 형식이 이상하다" };

        std::vector<std::string> out;
        for (const auto& r : j["reviews"])
            if (r.is_string())
                out.push_back(r.get<std::string>());

        if (out.empty())
            out.push_back("⭐️⭐️⭐️ 아무도 평가 안 남김");

        return out;
    }

    std::vector<std::string> scamReviews()
    {
        return {
            "⭐️⭐️⭐️⭐️⭐️ 인생 최고의 상점",
            "⭐️⭐️⭐️⭐️⭐️ 여기서만 삼",
            "⭐️⭐️⭐️⭐️⭐️ 사장님 신뢰 100%"
        };
    }
}

// ---------------------------
// 외부 공개 함수
std::vector<std::string>
ShopReviews::getRandomReviews(ShopType type, int count)
{
    //  10% 사기 후기
    if (chance(10))
        return scamReviews();

    auto reviews = loadReviews(jsonPathFromShopType(type));

    std::vector<std::string> result;
    std::uniform_int_distribution<> dist(0, (int)reviews.size() - 1);

    for (int i = 0; i < count; ++i)
        result.push_back(reviews[dist(rng())]);

    return result;
}
