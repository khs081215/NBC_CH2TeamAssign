
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "CityData.h"
#include "Store.h"

std::vector<City> getCities() {
    return {
        {
            "파도항",
            "항구인데 바람보다 상인 말발이 더 센 동네.\n"
            "특산품: 해산물, 무역품, 억울한 흥정썰",
            {
                {"게장집인데버거도함", ShopType::Food},
                {"문어다리늘림공방 (합법)", ShopType::Equipment},
                {"유나네잡화 (어제도열었음)", ShopType::General},
                {"멀미약은여기서", ShopType::Herbal},
                {"항구앞포장마차", ShopType::Food}
            }
        },
        {
            "풀내음골",
            "숲이 울창해서 휴대마법 신호 약함.\n"
            "특산품: 약초, 자연재료, 정체불명 가루",
            {
                {"산신령몰래차린약초방", ShopType::Herbal},
                {"건강한데맛없는집", ShopType::Food},
                {"숲속만물 (없으면직접캐옴)", ShopType::General},
                {"나무로대충만듦장비점", ShopType::Equipment}
            }
        },
        {
            "붉은언덕촌",
            "광산 끝나면 다들 말수 적어짐.\n"
            "특산품: 광석, 장비, 파스",
            {
                {"허리나간광부협회", ShopType::Equipment},
                {"고기무한아님식당", ShopType::Food},
                {"망치소리큰대장간", ShopType::General},
                {"파스만파는약초상", ShopType::Herbal}
            }
        },
        {
            "눈바람성",
            "눈 오면 그냥 그렇고 안 오면 축제함.\n"
            "특산품: 얼음, 눈, 콧물",
            {
                {"눈꽃슈퍼", ShopType::Food},
                {"빙판에서도안미끄러짐대장간", ShopType::Equipment},
                {"털모자전문점", ShopType::General},
                {"감기초기엔여기", ShopType::Herbal},
                {"코코아파는곳", ShopType::Food}
            }
        },
        {
            "볕좋은항",
            "햇빛 세서 다들 눈 찡그리고 다님.\n"
            "특산품: 해산물, 무역, 썬크림",
            {
                {"선셋앞노점", ShopType::Food},
                {"항구마트", ShopType::General},
                {"햇빛잘받는대장간", ShopType::Equipment},
                {"열사병오기전약국", ShopType::Herbal}
            }
        },
        {
            "수상한숲",
            "들어갈 때 계약서 씀.\n"
            "특산품: 마법재료, 약초, 설명회",
            {
                {"요정없음약초있음", ShopType::Herbal},
                {"마법재료세트오늘만할인", ShopType::General},
                {"마력충전식료품점", ShopType::Food},
                {"부적달린장비점", ShopType::Equipment}
            }
        },
        {
            "망치골",
            "금속 냄새랑 국밥 냄새가 섞인 동네.\n"
            "특산품: 무기, 방어구, 철가루",
            {
                {"철냄새나는대장간", ShopType::Equipment},
                {"광부국밥집", ShopType::Food},
                {"작업복도팜", ShopType::General},
                {"손목보호대전문약초상", ShopType::Herbal}
            }
        },
        {
            "돈많은동네",
            "말 끝에 항상 ‘투자’가 붙음.\n"
            "특산품: 금, 계약서, 스트레스",
            {
                {"금은보화아무거나삽니다", ShopType::General},
                {"부자도먹는분식집", ShopType::Food},
                {"황금비율장비점", ShopType::Equipment},
                {"불안할때먹는약초상", ShopType::Herbal}
            }
        },
        {
            "천둥마루",
            "번개 치면 그냥 창문 닫음.\n"
            "특산품: 번개맞은돌, 특수장비",
            {
                {"번개맞고도멀쩡한대장간", ShopType::Equipment},
                {"산위매점", ShopType::General},
                {"등산객라면집", ShopType::Food},
                {"감전되기전약초상", ShopType::Herbal}
            }
        },
        {
            "버들내",
            "할 일 없어서 이장님만 바쁨.\n"
            "특산품: 평화, 물고기, 낮잠",
            {
                {"버들약초방", ShopType::Herbal},
                {"마을슈퍼", ShopType::Food},
                {"강가잡화점", ShopType::General},
                {"농기구수리점", ShopType::Equipment}
            }
        }
    };
}

