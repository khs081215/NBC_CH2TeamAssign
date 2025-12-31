#include "CityData.h"

std::vector<City> getCities() {
    return {
        {"Poseidon","항구 도시, 아름다운 풍경.\n특산품: 해산물 & 무역 상품",
            { {"Danny's 게살버거", ShopType::General},
              {"Marin's 문어발확장", ShopType::Food},
              {"유나 상가", ShopType::Equipment} }
        },
        {"Verdantia","숲이 우거진 도시, 약초 풍부.\n특산품: 약재 & 자연 상품",
            { {"산신령's 한방치료", ShopType::Herbal},
              {"elena's 홀푸드마트", ShopType::Food} }
        },
        {"CrimsonHill","붉은 언덕 마을, 채광으로 유명.\n특산품: 금속 & 장비",
            { {"광부의 창고", ShopType::Equipment},
              {"언덕 식료품점", ShopType::Food},
              {"대장장이 상점", ShopType::General} }
        },
        {"Frostvale","눈과 얼음의 도시, 겨울 축제 개최",
            { {"눈꽃 마트", ShopType::Food},
              {"얼음 대장간", ShopType::Equipment} }
        },
        {"Sunport","태양 항구 도시, 해산물과 무역 번성",
            { {"선셋 마켓", ShopType::General},
              {"항구 식료품점", ShopType::Food} }
        },
        {"Mystwood","신비한 숲 마을, 약초와 요술 재료",
            { {"요정 약초상점", ShopType::Herbal},
              {"마법 식료품점", ShopType::Food} }
        },
        {"Ironforge","철광산 도시, 장비 제작 특화",
            { {"철광 대장간", ShopType::Equipment},
              {"광부용품점", ShopType::General} }
        },
        {"Goldshire","황금 마을, 상업과 투자 중심",
            { {"금은상회", ShopType::General},
              {"골드 마켓", ShopType::Food} }
        },
        {"Stormpeak","폭풍 산 정상 도시, 특수 장비 판매",
            { {"폭풍 대장간", ShopType::Equipment},
              {"산꼭대기 가게", ShopType::General} }
        },
        {"Willowbrook","강과 숲 사이의 평화로운 마을",
            { {"버드나무 약초상점", ShopType::Herbal},
              {"마을 식료품점", ShopType::Food} }
        }
    };
}
