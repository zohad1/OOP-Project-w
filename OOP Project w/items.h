#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Items {
public:
    string name;
    int id, price;

    Items() : id(0), price(0) {}
    Items(string name, int id, int price) : name(name), id(id), price(price) {}

    void displayItems() const {
        cout << id << ". " << name << " - $" << price << endl;
    }

    void saveinfile(ofstream& itemsfile) const {
        itemsfile << id << " " << name << " " << price << "\n";
    }

    static Items itemsfromfile(ifstream& itemsfile) {
        int fid, fprice;
        string fname;
        if (!(itemsfile >> fid >> fname >> fprice)) {
            // Return default if reading fails
            return Items("", 0, 0);
        }
        return Items(fname, fid, fprice);
    }

    static vector<Items> loadfromfile(const string& itemspath) {
        vector<Items> items;
        ifstream itemsfile(itemspath);
        if (!itemsfile.is_open()) {
            cout << "File not found: " << itemspath << endl;
            return items;
        }
        while (!itemsfile.eof()) {
            Items it = itemsfromfile(itemsfile);
            if (it.id != 0) {
                items.push_back(it);
            }
        }
        itemsfile.close();
        return items;
    }

    static void saveitemsinfile(const vector<Items>& ite, const string& itempath) {
        ofstream itemsfile(itempath);
        if (!itemsfile.is_open()) {
            cout << "File not found\n";
            return;
        }
        for (const auto& item : ite) {
            item.saveinfile(itemsfile);
        }
        itemsfile.close();
        cout << "Saved successfully\n";
    }

    // BUDGET SEARCH FUNCTIONS
    static void serach_by_budget(const vector<Items>& it) {
        int min, max;
        cout << "Enter the minimum budget: ";
        cin >> min;
        cout << "Enter the maximum budget: ";
        cin >> max;
        bool found = false;
        for (const auto& item : it) {
            if (item.price >= min && item.price <= max) {
                item.displayItems();
                found = true;
            }
        }
        if (!found) {
            cout << "No items found in this budget\n";
        }
    }
};
