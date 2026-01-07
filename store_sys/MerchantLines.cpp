#include "MerchantLines.h"

const std::map<MerchantPersonality, std::vector<std::string>> MerchantLines::buyLines = {
    {MerchantPersonality::Friendly, {"꺅너무감사합니다!","어머나영광이에요!","너무굉장한선택이에요!!!"}},
    {MerchantPersonality::Grumpy, {"결제완료되었습니다.","다음번에도들러주십시오.","좋습니다."}},
    {MerchantPersonality::Sarcastic, {"호그걸골라서어따쓸려고?.","샀으면 빨리 나가라.","뒤에손님 있는거 안보이나?"}},
    {MerchantPersonality::Animal, {"멍멍! 고마워용~","야옹~ 잘쓸개냥!","꿀꿀! 다음에도 또 와랴~"}}
};

const std::map<MerchantPersonality, std::vector<std::string>> MerchantLines::sellLines = {
    {MerchantPersonality::Friendly, {"너무고마워요~잘쓸게효","정말 이런걸주시면어떡해요~~~~!!!","앞으로도마니마니들러주셔야해요"}},
    {MerchantPersonality::Grumpy, {"판매성공적으로되셨습니다","거래완료되었습니다.","거래완료"}},
    {MerchantPersonality::Sarcastic, {"이거내가싸게사주는거야","쓸만한걸로 좀 가져와라.","끙 이런걸 가져오면 어따쓰겟노?"}},
    {MerchantPersonality::Animal, {"멍멍! 판매완료~","야옹~ 잘 받았개냥!","꿀꿀! 다음에도 또 팔아랴~"}}
};

const std::map<MerchantPersonality, std::vector<std::string>> MerchantLines::noGoldLines = {
    {MerchantPersonality::Friendly, {"아앗 ㅠㅠ 잔액이 부족해요!","골드 더 들고오실때까지 기다릴게요!!","헉 어쩌죠 ㅠㅠ"}},
    {MerchantPersonality::Grumpy, {"삐빅. 잔액 부족","잔액이 부족합니다.","돈이 모자랍니다."}},
    {MerchantPersonality::Sarcastic, {"돈도 없는게 왜왔노?","결제 오류 뜬다 함봐봐라","우리가 자원봉사단인줄 아냐?!"}},
    {MerchantPersonality::Animal, {"멍멍! 돈이 없개~","야옹~ 금액이 부족하개냥!","꿀꿀! 골드 더 가져와랴~"}}
};

const std::map<MerchantPersonality, std::vector<std::string>> MerchantLines::newStockLines = {
    {MerchantPersonality::Friendly, {"새물건들이 도착했어요~","업자님의 피와살과땀이 묻어있는 제품들","오늘도 한번 봐주고 가셔용!!"}},
    {MerchantPersonality::Grumpy, {"신재고 등장.","오늘밖에안팝니다","신제품 출현."}},
    {MerchantPersonality::Sarcastic, {"새상품 도착 함 와보이소.","여기 주목 하이소~~~","돈없으면 다음달에 결제 어쩔거노?"}},
    {MerchantPersonality::Animal, {"멍멍! 새물건 도착~","야옹~ 새로운 아이템 왔개냥!","꿀꿀! 오늘도 새 상품 준비됐개~"}}
};
