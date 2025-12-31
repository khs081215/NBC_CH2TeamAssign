#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <map>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
int _getch();
#endif

using namespace std;

// ---------- Constants ----------
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_ESC = 27;
const int STORE_DISPLAY_COUNT = 5;

// ---------- Colors ----------
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET  "\033[0m"

// ---------- Utility ----------
void sleep_ms(int ms);
void clearScreen();
void typeText(const string& text, int delay = 25);

// ---------- Shop Types ----------
enum class ShopType { General, Food, Equipment, Herbal };
enum class MerchantPersonality { Friendly, Grumpy, Sarcastic, Animal };

// ---------- Item Classes ----------
class ItemBase {
protected:
    string name, desc;
    int price, quantity;
    ShopType category;
public:
    ItemBase(string n, string d, int p, ShopType c, int q = 1);
    virtual ~ItemBase() {}
    virtual string getType() const = 0;
    virtual unique_ptr<ItemBase> clone() const = 0;
    virtual void displayInfo() const;
    string getName() const;
    int getPrice() const;
    int getQuantity() const;
    ShopType getCategory() const;
    void addQuantity(int q);
    void removeQuantity(int q);
};

class Consumable : public ItemBase {
    int restoreAmount;
public:
    Consumable(string n, string d, int p, int r, ShopType c, int q = 1);
    string getType() const override;
    unique_ptr<ItemBase> clone() const override;
};

class Equipable : public ItemBase {
    int attackBoost;
public:
    Equipable(string n, string d, int p, int atk, ShopType c, int q = 1);
    string getType() const override;
    unique_ptr<ItemBase> clone() const override;
};

// ---------- Shop ----------
class Shop {
    vector<unique_ptr<ItemBase>> store, masterItems;
    ShopType type;
    string ownerName;
    int day;
    MerchantPersonality personality;
public:
    Shop(ShopType t, const string& owner, MerchantPersonality p = MerchantPersonality::Friendly);
    string getOwnerName() const;
    int getDay() const;
    const vector<unique_ptr<ItemBase>>& getStore() const;
    MerchantPersonality getPersonality() const;
    void restock();
    void nextDay();
    bool buyItem(int idx, vector<unique_ptr<ItemBase>>& inv, int& gold);
    void sellItem(unique_ptr<ItemBase>& item, int qty, vector<unique_ptr<ItemBase>>& inv, int& gold);
};

// ---------- ShopUI ----------
class ShopUI {
    Shop& shop;
    vector<unique_ptr<ItemBase>>& inventory;
    int& gold;

    map<MerchantPersonality, vector<string>> buyLines;
    map<MerchantPersonality, vector<string>> sellLines;
    map<MerchantPersonality, vector<string>> noGoldLines;
    map<MerchantPersonality, vector<string>> newStockLines;

    void merchantSpeak(const string& msg);
    string randomLine(const map<MerchantPersonality, vector<string>>& linesMap);
    int selectInventoryItem();
    int selectSellQuantity(int maxQty);
public:
    ShopUI(Shop& s, vector<unique_ptr<ItemBase>>& inv, int& g);
    void run();
};

// ---------- City ----------
struct City {
    string name, description;
    vector<pair<string, ShopType>> shops;
};

// ---------- Shop Selection ----------
int selectShop(const City& city);

// ---------- Personality ----------
MerchantPersonality choosePersonality();

// ---------- 사용자용 상점 접근 함수 ----------
void goToStore(const City& currentCity, vector<unique_ptr<ItemBase>>& inventory, int& gold);
