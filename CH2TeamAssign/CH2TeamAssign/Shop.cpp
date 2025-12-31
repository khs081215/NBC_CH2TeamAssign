#include "Shop.h"

#ifndef _WIN32
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void sleep_ms(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typeText(const string& text, int delay) {
    for (char c : text) {
        cout << c << flush;
        sleep_ms(delay);
    }
    cout << endl;
}

// ---------- ItemBase ----------
ItemBase::ItemBase(string n, string d, int p, ShopType c, int q)
    : name(n), desc(d), price(p), category(c), quantity(q) {
}
void ItemBase::displayInfo() const {
    cout << "[" << getType() << "] " << name << " | " << desc
        << " | " << price << " G | Qty: " << quantity << endl;
}
string ItemBase::getName() const { return name; }
int ItemBase::getPrice() const { return price; }
int ItemBase::getQuantity() const { return quantity; }
ShopType ItemBase::getCategory() const { return category; }
void ItemBase::addQuantity(int q) { quantity += q; }
void ItemBase::removeQuantity(int q) { quantity = max(0, quantity - q); }

// ---------- Consumable ----------
Consumable::Consumable(string n, string d, int p, int r, ShopType c, int q)
    : ItemBase(n, d, p, c, q), restoreAmount(r) {
}
string Consumable::getType() const { return "Consumable"; }
unique_ptr<ItemBase> Consumable::clone() const { return make_unique<Consumable>(*this); }

// ---------- Equipable ----------
Equipable::Equipable(string n, string d, int p, int atk, ShopType c, int q)
    : ItemBase(n, d, p, c, q), attackBoost(atk) {
}
string Equipable::getType() const { return "Equipable"; }
unique_ptr<ItemBase> Equipable::clone() const { return make_unique<Equipable>(*this); }

// ---------- Shop ----------
Shop::Shop(ShopType t, const string& owner, MerchantPersonality p)
    : type(t), ownerName(owner), personality(p), day(1) {
    // --- masterItems 초기화 (원본 그대로) ---
    masterItems.push_back(make_unique<Consumable>("kechup", "극심한 HP 회복", 100, 50, ShopType::General));
    masterItems.push_back(make_unique<Consumable>("보리밥", "콩밥은 아직준비되지않음", 40, 10, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("킹크랩", "그리운맛.", 120, 30, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("식물이", "식집사가 애지중지키운 약초", 80, 20, ShopType::Herbal));
    masterItems.push_back(make_unique<Consumable>("사약", "만병치료제", 150, 0, ShopType::Herbal));
    masterItems.push_back(make_unique<Equipable>("포크", "포세이돈의 전설의 삼지창", 500, 10, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("냄비뚜껑", "주방템(방패)", 300, 5, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("4b연필", "미술인시티 최첨단무기", 250, 6, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("강철팬티", "가벼운 방어구.치명타방어", 400, 4, ShopType::Equipment));
    masterItems.push_back(make_unique<Consumable>("허브차", "체력을 천천히 회복", 30, 15, ShopType::Herbal));
    masterItems.push_back(make_unique<Consumable>("사과", "달콤한 사과, HP 5 회복", 10, 5, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("빵", "포만감 회복", 20, 10, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("엘릭서", "HP & MP 완전 회복", 300, 100, ShopType::General));
    masterItems.push_back(make_unique<Equipable>("나무검", "초보용 무기", 100, 2, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("철검", "평범한 검", 200, 5, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("강철갑옷", "방어력 +10", 500, 0, ShopType::Equipment));
    masterItems.push_back(make_unique<Equipable>("마법지팡이", "마법 공격 +8", 450, 8, ShopType::Equipment));
    masterItems.push_back(make_unique<Consumable>("당근", "HP 소량 회복", 5, 2, ShopType::Food));
    masterItems.push_back(make_unique<Consumable>("독약", "사용 시 HP 감소", 50, -20, ShopType::Herbal));
    restock();
}

string Shop::getOwnerName() const { return ownerName; }
int Shop::getDay() const { return day; }
const vector<unique_ptr<ItemBase>>& Shop::getStore() const { return store; }
MerchantPersonality Shop::getPersonality() const { return personality; }

void Shop::restock() {
    store.clear();
    random_device rd; mt19937 gen(rd());
    vector<ItemBase*> candidates;
    for (auto& i : masterItems) if (i->getCategory() == type || type == ShopType::General) candidates.push_back(i.get());
    shuffle(candidates.begin(), candidates.end(), gen);
    for (int i = 0; i < min(STORE_DISPLAY_COUNT, (int)candidates.size()); i++) {
        auto copy = candidates[i]->clone();
        copy->addQuantity(gen() % 4);
        store.push_back(move(copy));
    }
}

void Shop::nextDay() { day++; restock(); }

bool Shop::buyItem(int idx, vector<unique_ptr<ItemBase>>& inv, int& gold) {
    if (idx < 0 || idx >= store.size()) return false;
    if (gold < store[idx]->getPrice()) return false;
    gold -= store[idx]->getPrice();
    for (auto& i : inv) if (i->getName() == store[idx]->getName()) { i->addQuantity(1); store.erase(store.begin() + idx); return true; }
    inv.push_back(store[idx]->clone());
    store.erase(store.begin() + idx);
    return true;
}

void Shop::sellItem(unique_ptr<ItemBase>& item, int qty, vector<unique_ptr<ItemBase>>& inv, int& gold) {
    gold += (item->getPrice() * 60 / 100) * qty;
    item->removeQuantity(qty);
    if (item->getQuantity() == 0) inv.erase(remove_if(inv.begin(), inv.end(), [&](auto& i) { return i->getName() == item->getName(); }), inv.end());
}

// ---------- ShopUI ----------
ShopUI::ShopUI(Shop& s, vector<unique_ptr<ItemBase>>& inv, int& g)
    : shop(s), inventory(inv), gold(g) {
    buyLines = {
        {MerchantPersonality::Friendly,{"꺅너무감사합니다!","어머나영광이에요!","너무굉장한선택이에요!!!"}},
        {MerchantPersonality::Grumpy,{"결제완료되었습니다.","다음번에도들러주십시오.","좋습니다."}},
        {MerchantPersonality::Sarcastic,{"호그걸골라서어따쓸려고?.","샀으면 빨리 나가라.","뒤에손님 있는거 안보이나?"}},
        {MerchantPersonality::Animal, {"멍멍! 고마워용~","야옹~ 잘쓸개냥!","꿀꿀! 다음에도 또 와랴~"}}
    };
    sellLines = {
        {MerchantPersonality::Friendly,{"너무고마워요~잘쓸게효","정말 이런걸주시면어떡해요~~~~!!!","앞으로도마니마니들러주셔야해요"}},
        {MerchantPersonality::Grumpy,{"판매성공적으로되셨습니다","거래완료되었습니다.","거래완료"}},
        {MerchantPersonality::Sarcastic,{"이거내가싸게사주는거야","쓸만한걸로 좀 가져와라.","끙 이런걸 가져오면 어따쓰겟노?"}},
        {MerchantPersonality::Animal, {"멍멍! 판매완료~","야옹~ 잘 받았개냥!","꿀꿀! 다음에도 또 팔아랴~"}}
    };
    noGoldLines = {
        {MerchantPersonality::Friendly,{"아앗 ㅠㅠ 잔액이 부족해요!","골드 더 들고오실때까지 기다릴게요!!","헉 어쩌죠 ㅠㅠ"}},
        {MerchantPersonality::Grumpy,{"삐빅. 잔액 부족","잔액이 부족합니다.","돈이 모자랍니다."}},
        {MerchantPersonality::Sarcastic,{"돈도 없는게 왜왔노?","결제 오류 뜬다 함봐봐라","우리가 자원봉사단인줄 아냐?!"}},
        {MerchantPersonality::Animal, {"멍멍! 돈이 없개~","야옹~ 금액이 부족하개냥!","꿀꿀! 골드 더 가져와랴~"}}
    };
    newStockLines = {
        {MerchantPersonality::Friendly,{"새물건들이 도착했어요~","업자님의 피와살과땀이 묻어있는 제품들","오늘도 한번 봐주고 가셔용!!"}},
        {MerchantPersonality::Grumpy,{"신재고 등장.","오늘밖에안팝니다","신제품 출현."}},
        {MerchantPersonality::Sarcastic,{"새상품 도착 함 와보이소.","여기 주목 하이소~~~","돈없으면 다음달에 결제 어쩔거노?"}},
        {MerchantPersonality::Animal, {"멍멍! 새물건 도착~","야옹~ 새로운 아이템 왔개냥!","꿀꿀! 오늘도 새 상품 준비됐개~"}}
    };
    merchantSpeak("어서오세요! 천천히 둘러보세요~");
}

void ShopUI::merchantSpeak(const string& msg) {
    clearScreen();
    cout << shop.getOwnerName() << ": "; typeText(msg);
    cout << "\n(Press any key to continue)";
    _getch();
}

string ShopUI::randomLine(const map<MerchantPersonality, vector<string>>& linesMap) {
    auto& lines = linesMap.at(shop.getPersonality());
    static random_device rd; static mt19937 gen(rd());
    uniform_int_distribution<> dist(0, (int)lines.size() - 1);
    return lines[dist(gen)];
}

int ShopUI::selectInventoryItem() {
    if (inventory.empty()) return -1;
    int sel = 0;
    while (true) {
        clearScreen();
        cout << "=== INVENTORY (Select Item) ===\n\n";
        for (int i = 0; i < inventory.size(); i++) {
            if (i == sel) cout << COLOR_YELLOW << "> ";
            inventory[i]->displayInfo();
            if (i == sel) cout << COLOR_RESET;
        }
        cout << "\nUP/DOWN | ENTER Select | ESC Cancel\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < inventory.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) return sel;
        else if (key == KEY_ESC) return -1;
    }
}

int ShopUI::selectSellQuantity(int maxQty) {
    int qty = 1;
    while (true) {
        clearScreen();
        cout << "Select quantity to sell\n\n";
        cout << "Quantity: " << qty << " / " << maxQty << "\n\n";
        cout << "UP/DOWN Change | ENTER Confirm | ESC Cancel\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && qty < maxQty) qty++;
            if (key == KEY_DOWN && qty > 1) qty--;
        }
        else if (key == KEY_ENTER) return qty;
        else if (key == KEY_ESC) return -1;
    }
}

void ShopUI::run() {
    int sel = 0;
    while (true) {
        clearScreen();
        cout << "Gold: " << gold << " G\n";
        cout << "=== Day " << shop.getDay() << " ===\n\n";
        auto& store = shop.getStore();
        for (int i = 0; i < store.size(); i++) {
            if (i == sel) cout << COLOR_YELLOW << "> ";
            store[i]->displayInfo();
            if (i == sel) cout << COLOR_RESET;
        }
        cout << "\nUP/DOWN Move | ENTER Buy | S Sell | I Inventory | N Next Day | ESC Exit\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < store.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) {
            shop.buyItem(sel, inventory, gold) ? merchantSpeak(randomLine(buyLines)) : merchantSpeak(randomLine(noGoldLines));
        }
        else if (key == 's' || key == 'S') {
            int idx = selectInventoryItem();
            if (idx == -1) continue;
            int maxQty = inventory[idx]->getQuantity();
            int qty = selectSellQuantity(maxQty);
            if (qty == -1) continue;
            shop.sellItem(inventory[idx], qty, inventory, gold);
            merchantSpeak(randomLine(sellLines));
        }
        else if (key == 'i' || key == 'I') {
            clearScreen();
            cout << "=== INVENTORY ===\n\n";
            if (inventory.empty()) cout << "(Empty)\n";
            else for (auto& i : inventory) i->displayInfo();
            cout << "\nPress any key...";
            _getch();
        }
        else if (key == 'n' || key == 'N') {
            shop.nextDay();
            merchantSpeak(randomLine(newStockLines));
        }
        else if (key == KEY_ESC) break;
    }
}

// ---------- Shop Selection ----------
int selectShop(const City& city) {
    int sel = 0;
    while (true) {
        clearScreen();
        cout << "=== " << city.name << " ===\n";
        cout << city.description << "\n\n";
        for (int i = 0; i < city.shops.size(); i++) {
            if (i == sel) cout << COLOR_YELLOW << "> ";
            cout << city.shops[i].first << endl;
            if (i == sel) cout << COLOR_RESET;
        }
        cout << "\nENTER Enter Shop | ESC Back\n";
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && sel > 0) sel--;
            if (key == KEY_DOWN && sel < city.shops.size() - 1) sel++;
        }
        else if (key == KEY_ENTER) return sel;
        else if (key == KEY_ESC) return -1;
    }
}

// ---------- Personality ----------
MerchantPersonality choosePersonality() {
    int r = rand() % 100;
    if (r < 50) return MerchantPersonality::Friendly;
    else if (r < 70) return MerchantPersonality::Sarcastic;
    else if (r < 90) return MerchantPersonality::Animal;
    else return MerchantPersonality::Grumpy;
}

// ---------- 사용자용 상점 접근 함수 ----------
void goToStore(const City& currentCity, vector<unique_ptr<ItemBase>>& inventory, int& gold) {
    while (true) {
        int shopIdx = selectShop(currentCity);
        if (shopIdx == -1) break;
        string owner = currentCity.shops[shopIdx].first.substr(0, currentCity.shops[shopIdx].first.find('\''));
        MerchantPersonality p = choosePersonality();
        Shop shop(currentCity.shops[shopIdx].second, owner, p);
        ShopUI ui(shop, inventory, gold);
        ui.run();
        break; // 현재 상점 방문 후 바로 리턴
    }
}
