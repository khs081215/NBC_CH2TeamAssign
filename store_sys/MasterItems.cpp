#include "MasterItems.h"

std::vector<std::unique_ptr<ItemBase>> getMasterItems() {
    std::vector<std::unique_ptr<ItemBase>> items;

    // Consumable
    items.push_back(std::make_unique<Consumable>("kechup", "극심한 HP 회복", 100, 50, ShopType::General));
    items.push_back(std::make_unique<Consumable>("보리밥", "콩밥은 아직준비되지않음", 40, 10, ShopType::Food));
    items.push_back(std::make_unique<Consumable>("킹크랩", "그리운맛.", 120, 30, ShopType::Food));
    items.push_back(std::make_unique<Consumable>("식물이", "식집사가 애지중지키운 약초", 80, 20, ShopType::Herbal));
    items.push_back(std::make_unique<Consumable>("사약", "만병치료제", 150, 0, ShopType::Herbal));
    items.push_back(std::make_unique<Consumable>("허브차", "체력을 천천히 회복", 30, 15, ShopType::Herbal));
    items.push_back(std::make_unique<Consumable>("사과", "달콤한 사과, HP 5 회복", 10, 5, ShopType::Food));
    items.push_back(std::make_unique<Consumable>("빵", "포만감 회복", 20, 10, ShopType::Food));
    items.push_back(std::make_unique<Consumable>("엘릭서", "HP & MP 완전 회복", 300, 100, ShopType::General));
    items.push_back(std::make_unique<Consumable>("당근", "HP 소량 회복", 5, 2, ShopType::Food));
    items.push_back(std::make_unique<Consumable>("독약", "사용 시 HP 감소", 50, -20, ShopType::Herbal));

    // Equipable
    items.push_back(std::make_unique<Equipable>("포크", "포세이돈의 전설의 삼지창", 500, 10, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("냄비뚜껑", "주방템(방패)", 300, 5, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("4b연필", "미술인시티 최첨단무기", 250, 6, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("강철팬티", "가벼운 방어구.치명타방어", 400, 4, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("나무검", "초보용 무기", 100, 2, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("철검", "평범한 검", 200, 5, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("강철갑옷", "방어력 +10", 500, 0, ShopType::Equipment));
    items.push_back(std::make_unique<Equipable>("마법지팡이", "마법 공격 +8", 450, 8, ShopType::Equipment));

    return items;
}
