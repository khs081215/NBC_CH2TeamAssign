#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

class Player; // forward declaration

enum class ShopType { General, Food, Equipment, Herbal };

class ItemBase {
protected:
    string name, desc;
    int price;
    int quantity;
    ShopType category;

public:
    ItemBase(string n, string d, int p, ShopType c, int q = 1)
        : name(n), desc(d), price(p), category(c), quantity(q) {
    }
    virtual ~ItemBase() {}

    string getName() const { return name; }
    int GetPrice() const { return price; }
    int getQuantity() const { return quantity; }
    ShopType getCategory() const { return category; }

    void addQuantity(int q) { quantity += q; }
    void removeQuantity(int q) { quantity = max(0, quantity - q); }

    virtual void Use(Player& player) = 0;
    virtual string getType() const = 0;
    virtual unique_ptr<ItemBase> clone() const = 0;
    virtual void displayInfo() const {
        cout << name << " (" << desc << ") - 가격: " << price
            << " | 수량: " << quantity << endl;
    }
};


class Consumable : public ItemBase {
    int restoreAmount;
public:
    Consumable(string n, string d, int p, int r, ShopType c, int q = 1)
        : ItemBase(n, d, p, c, q), restoreAmount(r) {
    }

    string getType() const override { return "Consumable"; }
    unique_ptr<ItemBase> clone() const override { return make_unique<Consumable>(*this); }
    void Use(Player& player) override; // cpp에서 구현
};

class Equipable : public ItemBase {
    int attackBoost;
public:
    Equipable(string n, string d, int p, int atk, ShopType c, int q = 1)
        : ItemBase(n, d, p, c, q), attackBoost(atk) {
    }

    string getType() const override { return "Equipable"; }
    unique_ptr<ItemBase> clone() const override { return make_unique<Equipable>(*this); }
    int getAttackBoost() const { return attackBoost; }
    void Use(Player& player) override; // cpp에서 구현
};

