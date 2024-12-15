#pragma once
#include "items.h"

class Cart {
    vector<Items> cartitems;
    double totalprice;
public:
    Cart() : totalprice(0) {}

    void additem(const Items& item) {
        cartitems.push_back(item);
        totalprice += item.price;
    }

    void displaycart() const {
        cout << "Your Cart:\n";
        if (cartitems.empty()) {
            cout << "Your cart is empty\n";
            return;
        }
        for (const auto& item : cartitems) {
            item.displayItems();
        }
        cout << "Your total amount: $" << totalprice << endl;
    }

    const vector<Items>& getcartitems() const {
        return cartitems;
    }

    double gettotalprice() const {
        return totalprice;
    }

    void savetofile(const string& cartPath) const {
        ofstream file(cartPath);
        if (!file.is_open()) {
            cout << "Error: Cannot open file for saving cart.\n";
            return;
        }
        cout << "Saving cart data to " << cartPath << "...\n";
        file << totalprice << "\n";
        for (const auto& item : cartitems) {
            file << item.id << " " << item.name << " " << item.price << "\n";
        }
        file.close();
        cout << "Cart saved successfully to " << cartPath << ".\n";
    }

    void loadCartFromFile(const string& cartPath) {
        ifstream file(cartPath);
        if (!file.is_open()) {
            cout << "Error: Cannot open file for loading cart.\n";
            return;
        }

        cartitems.clear();
        totalprice = 0;

        file >> totalprice;
        while (!file.eof()) {
            int id, price;
            string name;
            file >> id >> name >> price;
            if (file.fail()) break;
            cartitems.push_back(Items(name, id, price));
        }
        file.close();
        cout << "Cart loaded successfully.\n";
    }
};
